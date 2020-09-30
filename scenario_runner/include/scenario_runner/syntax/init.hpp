// Copyright 2015-2020 Autoware Foundation. All rights reserved.
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

#ifndef SCENARIO_RUNNER__SYNTAX__INIT_HPP_
#define SCENARIO_RUNNER__SYNTAX__INIT_HPP_

#include <scenario_runner/syntax/init_actions.hpp>

namespace scenario_runner
{
inline namespace syntax
{
/* ==== Init ================================================================
 *
 * <xsd:complexType name="Init">
 *   <xsd:sequence>
 *     <xsd:element name="Actions" type="InitActions"/>
 *   </xsd:sequence>
 * </xsd:complexType>
 *
 * ======================================================================== */
struct Init
  : public InitActions
{
  template<typename Node, typename Scope>
  explicit Init(const Node & node, Scope & scope)
  : InitActions{readElement<InitActions>("Actions", node, scope)}
  {}
};
}
}  // namespace scenario_runner

#endif  // SCENARIO_RUNNER__SYNTAX__INIT_HPP_