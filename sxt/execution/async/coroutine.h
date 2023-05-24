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

#include <coroutine>

#include "sxt/execution/async/awaiter.h"
#include "sxt/execution/async/coroutine_promise.h"
#include "sxt/execution/async/future.h"

namespace sxt::xena {
//--------------------------------------------------------------------------------------------------
// operator co_await
//--------------------------------------------------------------------------------------------------
template <class T> awaiter<T> operator co_await(future<T>&& fut) noexcept {
  return awaiter<T>{std::move(fut)};
}
} // namespace sxt::xena

//--------------------------------------------------------------------------------------------------
// coroutine_traits
//--------------------------------------------------------------------------------------------------
namespace std {
template <class T, class... Args> struct coroutine_traits<sxt::xena::future<T>, Args...> {
  using promise_type = sxt::xena::coroutine_promise<T>;
};
} // namespace std
