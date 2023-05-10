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
#pragma once

#include <cstddef>
#include <cstdint>

#include "sxt/base/container/span.h"

namespace sxt::mtxpmp {
//--------------------------------------------------------------------------------------------------
// count_active_entries
//--------------------------------------------------------------------------------------------------
void count_active_entries(basct::span<size_t> counts,
                          basct::cspan<basct::cspan<uint64_t>> rows) noexcept;

inline void count_active_entries(basct::span<size_t> counts,
                                 basct::cspan<basct::span<uint64_t>> rows) noexcept {
  count_active_entries(counts,
                       {reinterpret_cast<const basct::cspan<uint64_t>*>(rows.data()), rows.size()});
}
} // namespace sxt::mtxpmp
