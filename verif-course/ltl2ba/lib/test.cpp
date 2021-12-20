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
#include "fsm.h"

using namespace model::ltl;
using namespace model::fsm;

int main() {
  const Formula &formula1 = G(P("p") >> F(P("q")));
  const Formula &formula2 = U(P("p"), G(P("q")));
  const Formula &formula3 = U(G(P("q")), P("p"));

  std::cout << "Formula1: " << std::endl;
  std::cout << formula1 << " w " << formula1.weight() << std::endl;
  std::cout << "Formula2: " << std::endl;
  std::cout << formula2 << " w " << formula2.weight() << std::endl;
  std::cout << formula3 << " w " << formula3.weight() << std::endl;
  
  std::cout << (formula3.weight() != formula2.weight()) << std::endl;

  Automaton automaton;
  automaton.add_state("s0");
  automaton.add_state("s1");
  automaton.add_state("s2");
  automaton.set_initial("s0");
  automaton.set_final("s1", 0);
  automaton.set_final("s2", 1);
  automaton.add_trans("s0", {"p"}, "s1");
  automaton.add_trans("s0", {"q"}, "s2");
  automaton.add_trans("s1", {}, "s0");
  automaton.add_trans("s1", {"p", "q"}, "s2");
  automaton.add_trans("s2", {}, "s2");

  std::cout << "Automaton: " << std::endl;
  std::cout << automaton << std::endl;

  return 0;
}

