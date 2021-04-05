#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <cmath>

void groupWrapper(std::istream& in, std::ostream& out);

void groupTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    groupWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void groupTestWrapper()
{
    TestInputType input1 = { "7\n", "1 2 3 1 2 3 4\n", "3\n" };
    std::string expected1 = "1 2 3 \n";
    groupTest(input1, expected1);

    TestInputType input2 = { "6\n", "1 1 1 2 2 3\n",  "1\n"};
    std::string expected2 = "1 \n";
    groupTest(input2, expected2);
/*
    TestInputType input5 = { "5\n", "2 4 5 2 10\n" };
    std::string expected5 = "542210\n";
    groupTest(input5, expected5);

    TestInputType input4 = { "2\n", "1000 4\n" };
    std::string expected4 = "41000\n";
    groupTest(input4, expected4);

    TestInputType input6 = { "2\n", "0 4\n" };
    std::string expected6 = "40\n";
    groupTest(input6, expected6);
*/
}

using DataType = uint64_t;
using IterType = std::vector<DataType>::const_iterator;

struct UniType
{
    DataType id;
    DataType students;
};

void groupWrapper(std::istream& in, std::ostream& out)
{
    DataType n = 0, k = 0, tmp = 0;
    in >> n;

    std::vector<UniType> unis(10001);
    for(size_t i = 0; i < 10001; i++)
    {
        unis[i].id = i;
        unis[i].students = 0;
    }
    for(size_t i = 0; i < n; i++)
    {
        in >> tmp;
        ++unis[tmp].students;
    }
    in >> k;
    if (!k)
        return;

    std::sort(unis.begin(), unis.end(), [] (UniType& lhs, UniType& rhs) {
        return lhs.students > rhs.students;
    });

    for (size_t i = 0; i < k; ++i)
    {
        out << unis[i].id << " ";
    }

    out << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        groupTestWrapper();
    else
        groupWrapper(std::cin, std::cout);
    std::cout << "\n";
}
