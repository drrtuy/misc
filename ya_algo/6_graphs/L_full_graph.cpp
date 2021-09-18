#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <iterator>
#include <unordered_set>

#pragma GCC target ("avx2")

void FullGWrapper(std::istream& in, std::ostream& out);

void FullGTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    FullGWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void FullGTestWrapper()
{
    TestInputType input = { "4 6\n1 2\n2 2\n2 3\n2 4\n3 4\n4 3\n" };
    std::string expected = "NO\n";
    FullGTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "3 5\n1 2\n2 1\n3 1\n2 3\n3 3\n" };
    expected = "YES\n";
    FullGTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";
}

enum Colors { white, grey, black };
using DataType = uint32_t;
using VertexId = DataType;
using Edge = std::pair<VertexId, VertexId>;

struct PairHash
{
    inline std::size_t operator()(const Edge& e) const
    {
        auto h32_1 = e.first;
        h32_1 ^= h32_1 >> 15;
        h32_1 *= 0x85EBCA77U;
        h32_1 ^= h32_1 >> 13;
        h32_1 *= 0xC2B2AE3DU;
        h32_1 ^= h32_1 >> 16;

        auto h = e.second;
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h ^ h32_1; 
    }
};

using UniqueEdgesSet = std::unordered_set<Edge, PairHash>;

void FullGWrapper(std::istream& in, std::ostream& out)
{
    DataType n, m;
    in >> n;
    in >> m;
    if (n == 1)
    {
        out << "YES\n";
        return;
    }
    if (m == 0 || n > m)
    {
        out << "NO\n";
        return;
    }

    const size_t magicNumber = n * (n - 1) / 2;

    UniqueEdgesSet uniqueEdges;

    VertexId u, v;
    for (size_t i = 0; i < m; ++i)
    {
        in >> u;
        in >> v;
        if (u == v)
            continue;
        VertexId minId = std::min(u, v);
        VertexId maxId = std::max(u, v);
        uniqueEdges.insert({minId, maxId});
    }

    if (uniqueEdges.size() == magicNumber)
        out << "YES\n";
    else
        out << "NO\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        FullGTestWrapper();
    else
        FullGWrapper(std::cin, std::cout);
    std::cout << "\n";
}
