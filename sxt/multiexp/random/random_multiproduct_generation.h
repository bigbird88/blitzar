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
#include <memory_resource>
#include <random>

#include "sxt/base/container/span.h"
#include "sxt/memory/management/managed_array_fwd.h"

namespace sxt::mtxi {
class index_table;
}

namespace sxt::mtxrn {
struct random_multiproduct_descriptor;

//--------------------------------------------------------------------------------------------------
// generate_random_multiproduct
//--------------------------------------------------------------------------------------------------
void generate_random_multiproduct(mtxi::index_table& products, size_t& num_inputs,
                                  size_t& num_entries, std::mt19937& rng,
                                  const random_multiproduct_descriptor& descriptor) noexcept;
} // namespace sxt::mtxrn
