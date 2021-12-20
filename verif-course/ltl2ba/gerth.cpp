#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <unordered_map>


#include "lib/ltl.h"
#include "lib/fsm.h"

using namespace model::ltl;
using namespace model::fsm;

void LTL2BAWrapper(std::istream& in, std::ostream& out);

void LTL2BATest(std::vector<std::string>& input, std::string& expected)
{
  std::stringstream in;
  std::stringstream ss;
  for (auto& e: input)
      in << e;
  LTL2BAWrapper(in, ss);
  std::string out = ss.str();
  std::cout << out;
  assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void LTL2BATestWrapper()
{
  const Formula &f1 = U(P("p"), G(P("q")));
  const Formula &f2 = U(G(P("q")), P("p"));
  assert(f1.weight() != f2.weight());
  const Formula &f3 = P("p");
  const Formula &f4 = P("q");
  assert(f1.weight() != f2.weight());

/*
  TestInputType input = { "4 4\n3 2\n4 3\n1 4\n1 2\n3\n",};
  std::string expected = "3 2 1 4 \n";
  LTL2BATest(input, expected);
  input.clear();
  expected.clear();

  input = { "2 1\n1 2\n1\n" };
  expected = "1 2 \n";
  LTL2BATest(input, expected);
  input.clear();
  expected.clear();


  input = { "123\n", "100003\n", "HaSH" };
  expected = "56156\n";
  LTL2BATest(input, expected);
  input.clear();
  expected.clear();
*/
}

using namespace model::ltl;
using LTLSetT = std::set<Formula>;
using NameT = uint32_t;
using NamesSetT = std::set<NameT>;
using IncomingT = std::unordered_map<NameT, NamesSetT>;
using Nodes2LTLSet = std::unordered_map<NameT, LTLSetT>;
const constexpr NameT Init = std::numeric_limits<NameT>::max();

NamesSetT Nodes;
IncomingT Incoming;
Nodes2LTLSet Now;
Nodes2LTLSet Next;
LTLSetT AP;

LTLSetT curr1UnionCurr(const Formula& f, const LTLSetT& aCurrent,
  const LTLSetT& aOld)
{
  LTLSetT resultSet;
  if (f.is_u()) {
    resultSet.insert(f.lhs());
  } else if (f.is_r()) {
    resultSet.insert(f.rhs());
  } else { //if (f.is_or())
    resultSet.insert(f.rhs());
  }
  for (auto& fFromOld: aOld)
    resultSet.erase(fFromOld);
  resultSet.insert(aCurrent.begin(), aCurrent.end());
  
  return resultSet;
}

LTLSetT curr2UnionCurr(const Formula& f, const LTLSetT& aCurrent,
  const LTLSetT& aOld)
{
  LTLSetT resultSet;
  if (f.is_u()) {
    resultSet.insert(f.rhs());
  } else if (f.is_r()) {
    resultSet.insert(f.lhs());
    resultSet.insert(f.rhs());
  } else { //if (f.is_or())
    resultSet.insert(f.lhs());
  }
  for (auto& fFromOld: aOld)
    resultSet.erase(fFromOld);
  resultSet.insert(aCurrent.begin(), aCurrent.end());
  
  return resultSet;
}

LTLSetT next1UnionNext(const Formula& f, const LTLSetT& aNext)
{
  LTLSetT resultSet;
  if (f.is_u() || f.is_r())
    resultSet.insert(f);
  resultSet.insert(aNext.begin(), aNext.end());
  return resultSet;
}

void expandGraph(LTLSetT aCurrent, LTLSetT aOld, LTLSetT aNext, NamesSetT aIncoming)
{
  for (auto& el : aCurrent)
    std::cout << "expandGraph aCurrent " << el << std::endl;
  if (aCurrent.empty()) {
    bool found = false;
    for (auto node: Nodes) {
      //if (node == Init)
      //  continue;

      auto globNextIter = Next.find(node);
      auto globNowIter = Now.find(node);

      if (globNextIter != Next.end() && globNowIter != Now.end()) {
        auto& nodesNext = (*globNextIter).second;
        auto& nodesNow = (*globNowIter).second;
        if (nodesNext == aNext && nodesNow == aOld) {
          Incoming[node].insert(aIncoming.begin(), aIncoming.end());
          found = true;
        }
      } // Node's Next and Now iters if
    } // Nodes loop
    if (!found) {
      NameT q = (!Nodes.empty()) ? *Nodes.rbegin() + 1 : 0;
      Nodes.insert(q);
      Incoming.insert({q, aIncoming});
      Now.insert({q, aOld});
      auto [nextIter, result] = Next.insert({q, aNext});
      auto& newNodesNext = (*nextIter).second;
      // the f's call uses copy construct that is slow to produce args.
      expandGraph(newNodesNext, {}, {}, {q}); 
    } // not found
  } // curent set empty if
  else {
    LTLSetT localCurrent = aCurrent;
    LTLSetT localOld = aOld;
    for (auto& f: aCurrent) {
      localCurrent.erase(f);
      localOld.insert(f);
      //for (auto& el : localOld)
      //  std::cout << "expandGraph else localOld " << el << std::endl;
      if (f.is_true() || f.is_false() ||
        (f.is_prop() && AP.find(f) != AP.end()) ||
        (f.is_neg_prop() && AP.find(f.arg()) != AP.end())) {
        if (f.is_false() || localOld.find(!f) != localOld.end()) // make !true => false conversion
          continue;
        else
          expandGraph(localCurrent, localOld, aNext, aIncoming);
      } else if (f.is_and()) {
        LTLSetT locCurrPlusOptionalLhsRhs = localCurrent;
        
        if (localOld.find(f.lhs()) == localOld.end())
          locCurrPlusOptionalLhsRhs.insert(f.lhs());

        if (localOld.find(f.rhs()) == localOld.end())
          locCurrPlusOptionalLhsRhs.insert(f.rhs());

        expandGraph(locCurrPlusOptionalLhsRhs, localOld, aNext, aIncoming);
      } else if (f.is_x()) {
        LTLSetT nextWXArg = aNext;
        nextWXArg.insert(f.arg());
        expandGraph(localCurrent, localOld, nextWXArg, aIncoming);
      } else if (f.is_or() || f.is_u() || f.is_r()) {
        LTLSetT curr1UnionCurrSet = curr1UnionCurr(f, localCurrent, localOld);
        LTLSetT curr2UnionCurrSet = curr2UnionCurr(f, localCurrent, localOld);
        LTLSetT next1UnionNextSet = next1UnionNext(f, aNext);
        expandGraph(curr1UnionCurrSet, localOld, next1UnionNextSet, aIncoming);
        expandGraph(curr2UnionCurrSet, localOld, aNext, aIncoming);
      }
    } // loop over aCurrent elements 
  } // top else
}

void scrapAPsFromLTLRec(const Formula &f, const bool seenX = false) {
  std::cout << "scrapAPsFromLTLRec f " << f << std::endl;
  if (f.is_neg_prop()) {
    AP.insert(f);
    std::cout << "scrapAPsFromLTLRec inserting f " << f << " AP.size() " << AP.size() << std::endl;
    return;
  }
  if (f.is_prop()) {
    AP.insert(f);
    std::cout << "scrapAPsFromLTLRec inserting f " << f << " AP.size() " << AP.size() << std::endl;
    if (seenX)
    {
      AP.insert(X(f));
      std::cout << "scrapAPsFromLTLRec inserting f " << X(f) << " AP.size() " << AP.size() << std::endl;
    }
    return;
  }

  if (f.has_lhs())
    scrapAPsFromLTLRec(f.lhs(), seenX ? seenX : f.is_x());

  if (f.has_rhs())
    scrapAPsFromLTLRec(f.rhs(), seenX ? seenX : f.is_x());
}

Automaton produceLGBA()
{
  Automaton ba;
  for (auto q: Nodes) {
    std::string qAsStr = "s" + std::to_string(q);
    ba.add_state(qAsStr);
    std::cout << "Incoming for node " << q << " : ";
    for (auto incQ: Incoming[q]) {
      std::cout << " " << incQ;
      if (incQ == Init) {
        ba.set_initial("s" + std::to_string(q));
        continue;
      }

      std::string incQeAsStr = "s" + std::to_string(incQ);
      ba.add_trans(incQeAsStr, {}, qAsStr);
      //std::cout << " " << incQ;
    }
    std::cout << std::endl;
  }
    
  return ba;
}

void LTL2BAWrapper(std::istream& in, std::ostream& out)
{
  //const Formula &f = G(P("p") >> X(P("q")));
  //const Formula &f = U(P("true"),(!P("p") || X(P("q"))));
  const Formula &f = !P("p") || U(P("true"), P("q"));
  //LTLSetT initialLTLSet, old, curr;
  //initialLTLSet.insert(formula1);
  scrapAPsFromLTLRec(f); // side-effect. Changes AP 
  expandGraph({f}, {}, {}, {Init}); // side-effects. Changes: Nodes, Incoming, Now, Next
  std::cout << " Nodes.size() " << Nodes.size() << " Incoming.size() " << Incoming.size()
    << " Now.size() " << Now.size() << " Next.size() " << Next.size() << " AP.size() " << AP.size() <<std::endl;
  Automaton ba(std::move(produceLGBA()));
  std::cout << ba << std::endl; 
}

int main(int argc, char** argv)
{
  //std::ios_base::sync_with_stdio(false);
  //std::cin.tie(NULL);
  // put any argument to follow unit testing path
  if (argc > 1)
      LTL2BATestWrapper();
  else
      LTL2BAWrapper(std::cin, std::cout);
  std::cout << "\n";
}
