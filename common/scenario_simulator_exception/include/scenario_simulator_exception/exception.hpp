// Copyright 2015-2021 Tier IV, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SCENARIO_SIMULATOR_EXCEPTION__EXCEPTION_HPP_
#define SCENARIO_SIMULATOR_EXCEPTION__EXCEPTION_HPP_

#include <scenario_simulator_exception/concatenate.hpp>
#include <stdexcept>
#include <utility>

namespace common
{
inline namespace scenario_simulator_exception
{
struct Error : public std::runtime_error
{
  template <typename... Ts>
  explicit Error(Ts &&... xs)
  : std::runtime_error{concatenate(std::forward<decltype(xs)>(xs)..., ".")}
  {
  }
};

#define DEFINE_ERROR_CATEGORY(TYPENAME)                                                       \
  struct TYPENAME : public Error                                                              \
  {                                                                                           \
    template <typename... Ts>                                                                 \
    explicit TYPENAME(Ts &&... xs) : Error{#TYPENAME ": ", std::forward<decltype(xs)>(xs)...} \
    {                                                                                         \
    }                                                                                         \
  }

// Autoware encountered some problem that led to a simulation failure.
DEFINE_ERROR_CATEGORY(AutowareError);

// Although there were no syntactic errors in the description of the scenario,
// differences in meaning and inconsistencies were found.
DEFINE_ERROR_CATEGORY(SemanticError);

// A problem occurred that interfered with the continuation of the simulation.
DEFINE_ERROR_CATEGORY(SimulationError);

// There is a syntactic error in the description of the scenario. Or you are
// using a feature that is not yet supported by our implementation.
DEFINE_ERROR_CATEGORY(SyntaxError);

#undef DEFINE_ERROR_CATEGORY

}  // namespace scenario_simulator_exception
}  // namespace common

#endif  // SCENARIO_SIMULATOR_EXCEPTION__EXCEPTION_HPP_