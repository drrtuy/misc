// Contest test run ID 48228488
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void parentWrapper(std::istream& in, std::ostream& out);

void testParent()
{
    std::stringstream in;
    in << "2\n";
    std::stringstream ss;
    parentWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "(())\n()()\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "3\n";
    parentWrapper(in, ss);
    out = ss.str();
    assert(out == "((()))\n(()())\n(())()\n()(())\n()()()\n");
}

const char LP = '(';
const char RP = ')';
using ResultOutputType = std::vector<std::string>;
const uint16_t powerOf2[] = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };

void parentRecursion(size_t n, size_t counterOpen, size_t counterClose, std::string seqPar, ResultOutputType& result)
{
    if (counterOpen + counterClose == 2 * n)
        result.push_back(seqPar);
   
    if (counterOpen < n)
        parentRecursion(n, counterOpen + 1, counterClose, seqPar + "(", result);
    if (counterOpen > counterClose)
        parentRecursion(n, counterOpen, counterClose + 1, seqPar + ")",result );
}

void parentWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0;
    in >> n;
    if (!n)
        return;
    ResultOutputType result;
    result.reserve(powerOf2[n]);
    parentRecursion(n, 0, 0, "", result);
    for (auto& e: result)
        out << e << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testParent();
    else
        parentWrapper(std::cin, std::cout);
    std::cout << "\n";
}
