/*
 * Copyright 2021 ISP RAS (http://www.ispras.ru)
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */

#include "ltl.h"

namespace model::ltl {

// This should take commutative property into account
size_t Formula::weight(size_t power) const {
    size_t weight = power * static_cast<size_t>(_kind);
    weight += _kind == ATOM ? _prop[0] - 'a' : 0;
    //std::cout << "weight power " << power << " weight " << weight << std::endl;
    if (!_lhs && !_rhs)
      return weight;

    size_t lhs_coef = _lhs_coef;
    size_t rhs_coef = (_kind == AND || _kind == OR) ? lhs_coef : _rhs_coef;

    weight += (_lhs) ? lhs_coef * _lhs->weight(power * _power_step) : 0;
    //std::cout << "weight after left power " << power << " weight " << weight << std::endl;       
    weight += (_rhs) ? rhs_coef * _rhs->weight(power * _power_step) : 0;
    //std::cout << "weight after right power " << power << " weight " << weight << std::endl;
    // A serious limitation props idents can be a single symbol only.

    return weight;
  }

std::ostream& operator <<(std::ostream &out, const Formula &formula) {
  switch (formula.kind()) {
  case Formula::ATOM:
    return out << formula.prop();
  case Formula::NOT:
    return out << "!(" << formula.arg() << ")";
  case Formula::AND:
    return out << "(" << formula.lhs() << ") && (" << formula.rhs() << ")";
  case Formula::OR:
    return out << "(" << formula.lhs() << ") || (" << formula.rhs() << ")";
  case Formula::IMPL:
    return out << "(" << formula.lhs() << ") -> (" << formula.rhs() << ")";
  case Formula::X:
    return out << "X(" << formula.arg() << ")";
  case Formula::G:
    return out << "G(" << formula.arg() << ")";
  case Formula::F:
    return out << "F(" << formula.arg() << ")";
  case Formula::U:
    return out << "(" << formula.lhs() << ") U (" << formula.rhs() << ")";
  case Formula::R:
    return out << "(" << formula.lhs() << ") R (" << formula.rhs() << ")";
  }

  return out;
}

} // namespace model::ltl
