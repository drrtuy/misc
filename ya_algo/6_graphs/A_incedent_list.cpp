#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

void incedentWrapper(std::istream& in, std::ostream& out);

void incedentTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    incedentWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void incedentTestWrapper()
{
    TestInputType input = { "5 3\n1 3\n2 3\n5 2\n",};
    std::string expected = "1 3 \n1 3 \n0 \n0 \n1 2 \n";
    incedentTest(input, expected);
    input.clear();
    expected.clear();

    input = { "5 4\n1 3\n2 3\n5 2\n5 1\n" };
    expected = "1 3 \n1 3 \n0 \n0 \n2 1 2 \n";
    incedentTest(input, expected);
    input.clear();
    expected.clear();

/*
    input = { "123\n", "100003\n", "hash" };
    expected = "6080\n";
    incedentTest(input, expected);
    input.clear();
    expected.clear();

    input = { "123\n", "100003\n", "HaSH" };
    expected = "56156\n";
    incedentTest(input, expected);
    input.clear();
    expected.clear();
*/
}


using DataType = uint16_t;
using Matrix = std::vector<std::vector<DataType>>;

void incedentWrapper(std::istream& in, std::ostream& out)
{
    Matrix m;
    DataType n, nV, u, v;
    in >> n;
    in >> nV;
    m.resize(n);
    for (size_t i = 0; i < nV; ++i)
    {
        in >> u;
        in >> v;
        m[u - 1].push_back(v);
    }
    for (auto& neighList : m)
    {
        out << neighList.size();
        out << " ";
        std::sort(neighList.begin(), neighList.end(), std::less<DataType>()); 
        for (auto neigh: neighList)
            out << neigh << " ";
        out << "\n";
    }
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        incedentTestWrapper();
    else
        incedentWrapper(std::cin, std::cout);
    std::cout << "\n";
}
