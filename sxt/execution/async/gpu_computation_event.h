/** Proofs GPU - Space and Time's cryptographic proof algorithms on the CPU and GPU.
 *
 * Copyright 2023-present Space and Time Labs, Inc.
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

#include "sxt/base/device/event.h"
#include "sxt/execution/async/computation_handle.h"
#include "sxt/execution/async/promise.h"
#include "sxt/execution/schedule/pollable_event.h"

namespace sxt::xena {
//--------------------------------------------------------------------------------------------------
// gpu_computation_event
//--------------------------------------------------------------------------------------------------
template <class T = void> class gpu_computation_event final : public xens::pollable_event {
public:
  gpu_computation_event(basdv::event&& event, computation_handle&& computation,
                        xena::promise<T>&& promise) noexcept
      : event_{std::move(event)}, computation_{std::move(computation)},
        promise_{std::move(promise)} {}

  gpu_computation_event(basdv::event&& event, xena::promise<T>&& promise) noexcept
      : event_{std::move(event)}, promise_{std::move(promise)} {}

  xena::promise<T>& promise() noexcept { return promise_; }

  // xens::pollable_event
  bool ready() noexcept override { return event_.query_is_ready(); }

  void invoke() noexcept override { promise_.make_ready(); }

private:
  basdv::event event_;
  computation_handle computation_;
  xena::promise<T> promise_;
};

extern template class gpu_computation_event<void>;
} // namespace sxt::xena
