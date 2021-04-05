#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void triangleWrapper(std::istream& in, std::ostream& out);

void triangleTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    triangleWrapper(in, ss);
    std::string out = ss.str();
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void triangleTestWrapper()
{
    TestInputType input1 = { "4\n", "6 3 3 2\n", };
    std::string expected1 = "8\n";
    triangleTest(input1, expected1);

    TestInputType input2 = { "6\n" , "5 3 7 2 8 3\n", };
    std::string expected2 = "20\n";
    triangleTest(input2, expected2);

/*
    TestInputType input3 = { "0 1000\n", "\n", };
    std::string expected3 = "0\n";
    triangleTest(input3, expected3);

    TestInputType input4 = { "3 0\n", "1 2 3\n", };
    std::string expected4 = "0\n";
    triangleTest(input4, expected4);

    TestInputType input5 = { "3\n", "2 5 3\n", "1\n", "1\n", };
    std::string expected5 = "0\n";
    triangleTest(input5, expected5);

    TestInputType input6 = { "3\n", "2 10 3\n", "6\n", "0 0 0 20 4 2\n", };
    std::string expected6 = "3\n";
    triangleTest(input6, expected6);

    TestInputType input7 = { "3\n", "1 1 1\n", "4\n", "0 0 0 0\n", };
    std::string expected7 = "0\n";
    triangleTest(input7, expected7);
*/
}

using DataType = uint64_t;
using IterType = std::vector<DataType>::const_iterator;

void triangleWrapper(std::istream& in, std::ostream& out)
{
    DataType n = 0, tmp = 0;
    in >> n;

    std::vector<DataType> lengths;
    lengths.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        in >> tmp;
        lengths.push_back(tmp);
    }

    std::sort(lengths.begin(), lengths.end(), std::greater<DataType>());

    IterType i1 = lengths.begin();
    IterType i2 = i1 + 1;
    IterType i3 = i2 + 1;
    while (i3 < lengths.end() && *i1 >= *i2 + *i3)
    {
        ++i1;
        ++i2;
        ++i3;
    }

    out << *i1 + *i2 + *i3 << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        triangleTestWrapper();
    else
        triangleWrapper(std::cin, std::cout);
    std::cout << "\n";
}
