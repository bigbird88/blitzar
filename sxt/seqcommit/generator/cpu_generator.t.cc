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
#include "sxt/seqcommit/generator/cpu_generator.h"

#include "sxt/base/test/unit_test.h"
#include "sxt/seqcommit/test/test_generators.h"

using namespace sxt;
using namespace sxt::sqcgn;

TEST_CASE("run computation tests") { sqctst::test_pedersen_get_generators(cpu_get_generators); }
