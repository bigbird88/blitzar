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

namespace sxt::mtxrn {
//--------------------------------------------------------------------------------------------------
// random_multiproduct_descriptor
//--------------------------------------------------------------------------------------------------
struct random_multiproduct_descriptor {
  size_t min_sequence_length = 1;
  size_t max_sequence_length = 10;
  size_t min_num_sequences = 2;
  size_t max_num_sequences = 10;
  size_t max_num_inputs = 10;
};
} // namespace sxt::mtxrn
