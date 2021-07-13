#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void radixWrapper(std::istream& in, std::ostream& out);

void radixTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    radixWrapper(in, ss);
    std::string out = ss.str();
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void radixTestWrapper()
{
    TestInputType input1 = { "7\n", "0 2 1 2 0 0 1\n", };
    std::string expected1 = "0 0 0 1 1 2 2 \n";
    radixTest(input1, expected1);

    TestInputType input2 = { "5\n" , "2 1 2 0 1\n", };
    std::string expected2 = "0 1 1 2 2 \n";
    radixTest(input2, expected2);

    TestInputType input3 = { "5\n", "0 0 0 0 0\n", };
    std::string expected3 = "0 0 0 0 0 \n";
    radixTest(input3, expected3);

/*
    TestInputType input4 = { "3 0\n", "1 2 3\n", };
    std::string expected4 = "0\n";
    radixTest(input4, expected4);

    TestInputType input5 = { "3\n", "2 5 3\n", "1\n", "1\n", };
    std::string expected5 = "0\n";
    radixTest(input5, expected5);

    TestInputType input6 = { "3\n", "2 10 3\n", "6\n", "0 0 0 20 4 2\n", };
    std::string expected6 = "3\n";
    radixTest(input6, expected6);

    TestInputType input7 = { "3\n", "1 1 1\n", "4\n", "0 0 0 0\n", };
    std::string expected7 = "0\n";
    radixTest(input7, expected7);
*/
}

using DataType = uint64_t;
using IterType = std::vector<DataType>::const_iterator;

void radixWrapper(std::istream& in, std::ostream& out)
{
    DataType n = 0, tmp = 0;
    in >> n;
    if (!n)
        return;

    std::vector<DataType> sorted(3, 0);
    for(size_t i = 0; i < n; i++)
    {
        in >> tmp;
        ++sorted[tmp];
    }

    for (DataType i = 0; i < sorted.size(); ++i)
    {
        for (DataType counter = 0; counter < sorted[i]; ++counter)
            out << i << " ";
    }
    out << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        radixTestWrapper();
    else
        radixWrapper(std::cin, std::cout);
    std::cout << "\n";
}
