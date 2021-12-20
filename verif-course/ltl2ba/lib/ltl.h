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

#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace model::ltl {

class Formula final {
public:
  enum Kind {
    ATOM = 1, // Atomic proposition: p
    NOT = 2,  // Negation: ~A
    AND = 3,  // Conjunction: (A1 & A2)
    OR = 4,   // Disjunction: (A1 | A2)
    IMPL = 5, // Implication: (A1 -> A2)
    X = 6,    // NeXt time: X{A}
    G = 7,    // Globally: G{A}
    F = 8,    // In the Future: F{A}
    U = 9,    // Until: (A1 U A2)
    R = 0,     // Release: (A1 R A2)
  };
  static const constexpr size_t _power_step = 100ULL;
  static const constexpr size_t _lhs_coef = 1ULL;
  static const constexpr size_t _rhs_coef = 2ULL;

  const Formula& operator !() const;
  const Formula& operator &&(const Formula &rhs) const;
  const Formula& operator ||(const Formula &rhs) const;
  const Formula& operator >>(const Formula &rhs) const;

  friend const Formula& P(const std::string &prop);
  friend const Formula& X(const Formula &arg);
  friend const Formula& G(const Formula &arg);
  friend const Formula& F(const Formula &arg);
  friend const Formula& U(const Formula &lhs, const Formula &rhs);
  friend const Formula& R(const Formula &lhs, const Formula &rhs);

  Kind kind() const { return _kind; }
  std::string prop() const { return _prop; }
  
  bool is_and() const { return _kind == AND; }
  bool is_false() const { return _kind == ATOM && _prop == "false"; }; // case sensitive
  bool is_neg_prop() const { return _kind == NOT && _lhs->kind() == ATOM; }
  bool is_or() const { return _kind == OR; }
  bool is_prop() const { return _kind == ATOM; }
  bool is_r() const { return _kind == R; }
  bool is_true() const { return _kind == ATOM && _prop == "true"; }; // case sensitive
  bool is_u() const { return _kind == U; }
  bool is_x() const { return _kind == X; }
  bool is_x_with_prop() const { return _kind == X && arg().kind() == ATOM; }
 
  const Formula& arg() const { return *_lhs; }
  const Formula& lhs() const { return *_lhs; }
  const Formula& rhs() const { return *_rhs; }
  
  bool has_lhs() const { return _lhs != nullptr; }
  bool has_rhs() const { return _rhs != nullptr; }

  bool operator<(const Formula &rhs) const {
    return weight() < rhs.weight();
  }
  
  bool operator==(const Formula &rhs) const {
    return weight() == rhs.weight();
  }

  size_t weight(size_t power = 1) const;
  

private:
  Formula(Kind kind, const std::string &prop, const Formula *lhs, const Formula *rhs):
    _kind(kind), _prop(prop), _lhs(lhs), _rhs(rhs) {}

  Formula(const std::string &prop):
    Formula(ATOM, prop, nullptr, nullptr) {}

  Formula(Kind kind, const Formula *arg):
    Formula(kind, "", arg, nullptr) {}

  Formula(Kind kind, const Formula *lhs, const Formula *rhs):
    Formula(kind, "", lhs, rhs) {}

  static const Formula& alloc(const Formula *formula) {
    static std::vector<std::unique_ptr<const Formula>> formulae;
    formulae.push_back(std::unique_ptr<const Formula>(formula));
    return *formula;
  }

  const Kind _kind;
  const std::string _prop;
  const Formula *_lhs;
  const Formula *_rhs;
};

inline const Formula& Formula::operator !() const {
  return alloc(new Formula(NOT, this));
}

inline const Formula& Formula::operator &&(const Formula &rhs) const {
  return alloc(new Formula(AND, this, &rhs));
}

inline const Formula& Formula::operator ||(const Formula &rhs) const {
  return alloc(new Formula(OR, this, &rhs));
}

inline const Formula& Formula::operator >>(const Formula &rhs) const {
  return alloc(new Formula(IMPL, this, &rhs));
}

inline const Formula& P(const std::string &prop) {
  return Formula::alloc(new Formula(prop));
}

inline const Formula& X(const Formula &arg) {
  return Formula::alloc(new Formula(Formula::X, &arg));
}

inline const Formula& G(const Formula &arg) {
  return Formula::alloc(new Formula(Formula::G, &arg));
}

inline const Formula& F(const Formula &arg) {
  return Formula::alloc(new Formula(Formula::F, &arg));
}

inline const Formula& U(const Formula &lhs, const Formula &rhs) {
  return Formula::alloc(new Formula(Formula::U, &lhs, &rhs));
}

inline const Formula& R(const Formula &lhs, const Formula &rhs) {
  return Formula::alloc(new Formula(Formula::R, &lhs, &rhs));
}

std::ostream& operator <<(std::ostream &out, const Formula &formula);

} // namespace model::ltl
