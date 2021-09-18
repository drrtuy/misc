#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void stockGWrapper(std::istream& in, std::ostream& out);

void stockGTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    stockGWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void stockGTestWrapper()
{
    TestInputType input = { "6\n7 1 5 3 6 4\n",};
    std::string expected = "7\n";
    stockGTest(input, expected);
    input.clear();
    expected.clear();

    input = { "5\n1 2 3 4 5\n" };
    expected = "4\n";
    stockGTest(input, expected);
    input.clear();
    expected.clear();


    input = { "6\n1 12 12 16 1 8\n" };
    expected = "22\n";
    stockGTest(input, expected);
    input.clear();
    expected.clear();
/*
    input = { "123\n", "100003\n", "HaSH" };
    expected = "56156\n";
    stockGTest(input, expected);
    input.clear();
    expected.clear();
*/
}


using DataType = uint16_t;
using History = std::vector<DataType>;

void stockGWrapper(std::istream& in, std::ostream& out)
{
    DataType n, p;
    in >> n;
    History h(n);
    for (size_t i = 0; i < n; ++i)
    {
        in >> p;
        h[i] = p;
    }

    if (std::is_sorted(h.begin(), h.end()))
    {
        out << h.back() - h.front() << "\n";
        return;
    }

    bool hasPaper = false;
    uint32_t profit = 0;
    for (auto i = h.begin(); i < h.end() - 1; ++i)
    {
        if (!hasPaper && *(i + 1) - *i > 0)
        {
            profit -= *i;
            hasPaper = true;
        }
        else if (hasPaper && *i > *(i + 1))
        {
            profit += *i;
            hasPaper = false;
        }
    }
    if (hasPaper)
        profit += h.back();
    out << profit << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        stockGTestWrapper();
    else
        stockGWrapper(std::cin, std::cout);
    std::cout << "\n";
}
