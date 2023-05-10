/** Proofs GPU - Space and Time's cryptographic proof algorithms on the CPU and GPU.
 *
 * Copyright 2023 Space and Time Labs, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "sxt/multiexp/pippenger/multiproduct_table.h"

#include <algorithm>

#include "sxt/base/bit/count.h"
#include "sxt/base/bit/iteration.h"
#include "sxt/base/bit/span_op.h"
#include "sxt/base/container/blob_array.h"
#include "sxt/base/error/assert.h"
#include "sxt/base/num/divide_up.h"
#include "sxt/multiexp/base/digit_utility.h"
#include "sxt/multiexp/base/exponent_sequence.h"
#include "sxt/multiexp/index/index_table.h"

namespace sxt::mtxpi {
//--------------------------------------------------------------------------------------------------
// init_multiproduct_table
//--------------------------------------------------------------------------------------------------
static void init_multiproduct_table(mtxi::index_table& table, size_t max_entries,
                                    const basct::blob_array& output_digit_or_all) noexcept {
  size_t row_count = 0;
  for (auto digit : output_digit_or_all) {
    row_count += basbt::pop_count(digit);
  }
  table.reshape(row_count, max_entries + 2 * row_count);
}

//--------------------------------------------------------------------------------------------------
// init_multiproduct_output_rows
//--------------------------------------------------------------------------------------------------
static uint64_t* init_multiproduct_output_rows(
    basct::span<basct::span<uint64_t>> rows, size_t& multiproduct_output_index,
    uint64_t* entry_data, std::vector<size_t>& row_counts, std::vector<uint8_t>& digit,
    const mtxb::exponent_sequence& sequence, basct::cspan<uint8_t> digit_or_all) noexcept {
  std::fill(row_counts.begin(), row_counts.end(), 0);
  auto radix_log2 = row_counts.size();
  for (size_t term_index = 0; term_index < sequence.n; ++term_index) {
    basct::cspan<uint8_t> e{sequence.data + term_index * sequence.element_nbytes,
                            sequence.element_nbytes};
    auto digit_last = mtxb::get_last_digit(e, radix_log2);
    for (size_t digit_index = 0; digit_index < digit_last; ++digit_index) {
      mtxb::extract_digit(digit, e, radix_log2, digit_index);
      basbt::for_each_bit(digit, [&](size_t bit_index) noexcept { ++row_counts[bit_index]; });
    }
  }
  for (auto count : row_counts) {
    if (count == 0) {
      continue;
    }
    auto output_index = multiproduct_output_index++;
    auto& row = rows[output_index];
    row = {entry_data, 2};
    row[0] = output_index;
    row[1] = 0;
    entry_data += count + 2;
  }
  return entry_data;
}

//--------------------------------------------------------------------------------------------------
// make_digit_index_array
//--------------------------------------------------------------------------------------------------
void make_digit_index_array(basct::span<size_t> array, size_t first,
                            basct::cspan<uint8_t> or_all) noexcept {
  basbt::for_each_bit(or_all, [&](size_t index) noexcept { array[index] = first++; });
}

//--------------------------------------------------------------------------------------------------
// make_multiproduct_table
//--------------------------------------------------------------------------------------------------
size_t make_multiproduct_table(mtxi::index_table& table,
                               basct::cspan<mtxb::exponent_sequence> exponents, size_t max_entries,
                               const basct::blob_array& term_or_all,
                               const basct::blob_array& output_digit_or_all,
                               size_t radix_log2) noexcept {
  SXT_DEBUG_ASSERT(exponents.size() == output_digit_or_all.size());

  init_multiproduct_table(table, max_entries, output_digit_or_all);

  auto digit_num_bytes = basn::divide_up(radix_log2, 8ul);
  std::vector<uint8_t> digit(digit_num_bytes);
  std::vector<size_t> index_array(radix_log2);
  auto entry_data = table.entry_data();
  auto rows = table.header();
  size_t multiproduct_output_index = 0;
  size_t max_inputs = 0;
  for (size_t output_index = 0; output_index < output_digit_or_all.size(); ++output_index) {
    auto digit_or_all = output_digit_or_all[output_index];
    auto sequence = exponents[output_index];

    auto bit_index_first = multiproduct_output_index;
    entry_data = init_multiproduct_output_rows(rows, multiproduct_output_index, entry_data,
                                               index_array, digit, sequence, digit_or_all);
    make_digit_index_array(index_array, bit_index_first, digit_or_all);
    size_t input_first = 0;
    for (size_t term_index = 0; term_index < sequence.n; ++term_index) {
      basct::cspan<uint8_t> e{sequence.data + term_index * sequence.element_nbytes,
                              sequence.element_nbytes};
      auto digit_last = mtxb::get_last_digit(e, radix_log2);
      size_t input_offset = 0;
      for (size_t digit_index = 0; digit_index < digit_last; ++digit_index) {
        mtxb::extract_digit(digit, e, radix_log2, digit_index);
        basbt::for_each_bit(digit, [&](size_t bit_index) noexcept {
          auto& row = rows[index_array[bit_index]];
          auto sz = row.size();
          row = {row.data(), row.size() + 1};
          row[sz] = input_first + input_offset;
        });
        input_offset += static_cast<size_t>(
            !mtxb::is_digit_zero(term_or_all[term_index], radix_log2, digit_index));
      }
      input_first += mtxb::count_nonzero_digits(term_or_all[term_index], radix_log2);
    }
    max_inputs = std::max(input_first, max_inputs);
  }
  return max_inputs;
}
} // namespace sxt::mtxpi
