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

#include <cstdint>
#include <random>

#include "sxt/multiexp/index/clump2_descriptor.h"

namespace sxt::mtxi {
//--------------------------------------------------------------------------------------------------
// random_clump2
//--------------------------------------------------------------------------------------------------
struct random_clump2 {
  uint64_t clump_size;
  uint64_t clump_index;
  uint64_t index1;
  uint64_t index2;
};

//--------------------------------------------------------------------------------------------------
// generate_random_clump2
//--------------------------------------------------------------------------------------------------
void generate_random_clump2(random_clump2& clump, std::mt19937& rng) noexcept;
} // namespace sxt::mtxi
