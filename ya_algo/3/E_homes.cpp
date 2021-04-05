#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void homesWrapper(std::istream& in, std::ostream& out);

void homesTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    homesWrapper(in, ss);
    std::string out = ss.str();
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void homesTestWrapper()
{
    TestInputType input1 = { "3 300\n", "999 999 999", };
    std::string expected1 = "0\n";
    homesTest(input1, expected1);

    TestInputType input2 = { "3 1000\n", "350 999 200\n", };
    std::string expected2 = "2\n";
    homesTest(input2, expected2);

    TestInputType input3 = { "0 1000\n", "\n", };
    std::string expected3 = "0\n";
    homesTest(input3, expected3);

    TestInputType input4 = { "3 0\n", "1 2 3\n", };
    std::string expected4 = "0\n";
    homesTest(input4, expected4);

/*
    TestInputType input5 = { "3\n", "2 5 3\n", "1\n", "1\n", };
    std::string expected5 = "0\n";
    homesTest(input5, expected5);

    TestInputType input6 = { "3\n", "2 10 3\n", "6\n", "0 0 0 20 4 2\n", };
    std::string expected6 = "3\n";
    homesTest(input6, expected6);

    TestInputType input7 = { "3\n", "1 1 1\n", "4\n", "0 0 0 0\n", };
    std::string expected7 = "0\n";
    homesTest(input7, expected7);
*/
}

using DataType = uint64_t;
using IterType = std::vector<DataType>::const_iterator;

void homesWrapper(std::istream& in, std::ostream& out)
{
    DataType n = 0, p = 0, tmp = 0;
    in >> n;
    in >> p;
    if (!n || !p)
    {
        out << "0\n";
        return;
    }

    std::vector<DataType> homePrices;
    homePrices.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        in >> tmp;
        homePrices.push_back(tmp);
    }

    std::sort(homePrices.begin(), homePrices.end(), std::less<DataType>());

    DataType sum = 0;
    DataType count = 0;   

    IterType iter = homePrices.begin();
    while (iter < homePrices.end() && ((sum = sum + *iter) <= p))
    {
        ++count;
        ++iter;
    }

    out << count << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        homesTestWrapper();
    else
        homesWrapper(std::cin, std::cout);
    std::cout << "\n";
}
