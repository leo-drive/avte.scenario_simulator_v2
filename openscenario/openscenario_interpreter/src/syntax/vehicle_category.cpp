// Copyright 2015-2020 Tier IV, Inc. All rights reserved.
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

#include <openscenario_interpreter/syntax/vehicle_category.hpp>
#include <sstream>
#include <string>

namespace openscenario_interpreter
{
inline namespace syntax
{
std::istream & operator>>(std::istream & is, VehicleCategory & category)
{
  std::string buffer;

  is >> buffer;

#define BOILERPLATE(IDENTIFIER)                   \
  if (buffer == #IDENTIFIER) {                    \
    category.value = VehicleCategory::IDENTIFIER; \
    return is;                                    \
  }                                               \
  static_assert(true, "")

  BOILERPLATE(bicycle);
  BOILERPLATE(bus);
  BOILERPLATE(car);
  BOILERPLATE(motorbike);
  BOILERPLATE(truck);

#undef BOILERPLATE

#define BOILERPLATE(IDENTIFIER)                                                              \
  if (buffer == #IDENTIFIER) {                                                               \
    std::stringstream ss;                                                                    \
    ss << "given value \'";                                                                  \
    ss << buffer;                                                                            \
    ss << "\' is valid OpenSCENARIO value of type VehicleCategory, but it is not supported"; \
    throw ImplementationFault(ss.str());                                                     \
  }                                                                                          \
  static_assert(true, "")

  BOILERPLATE(semitrailer);
  BOILERPLATE(trailer);
  BOILERPLATE(train);
  BOILERPLATE(tram);
  BOILERPLATE(van);

#undef BOILERPLATE

  std::stringstream ss{};
  ss << "unexpected value \'" << buffer << "\' specified as type VehicleCategory";
  throw SyntaxError{ss.str()};
}

std::ostream & operator<<(std::ostream & os, const VehicleCategory & category)
{
#define BOILERPLATE(NAME)     \
  case VehicleCategory::NAME: \
    return os << #NAME;

  switch (category) {
    BOILERPLATE(bicycle);
    BOILERPLATE(bus);
    BOILERPLATE(car);
    BOILERPLATE(motorbike);
    BOILERPLATE(semitrailer);
    BOILERPLATE(trailer);
    BOILERPLATE(train);
    BOILERPLATE(tram);
    BOILERPLATE(truck);
    BOILERPLATE(van);

    default:
      std::stringstream ss;
      ss << "enum class VehicleCategory holds unexpected value "
         << static_cast<VehicleCategory::value_type>(category);
      throw ImplementationFault(ss.str());
  }

#undef BOILERPLATE
}
}  // namespace syntax
}  // namespace openscenario_interpreter