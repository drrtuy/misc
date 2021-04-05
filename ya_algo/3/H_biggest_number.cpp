#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <cmath>

void biggestNumberWrapper(std::istream& in, std::ostream& out);

void biggestNumberTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    biggestNumberWrapper(in, ss);
    std::string out = ss.str();
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void biggestNumberTestWrapper()
{
    TestInputType input1 = { "3\n", "15 56 2\n", };
    std::string expected1 = "56215\n";
    biggestNumberTest(input1, expected1);

    TestInputType input2 = { "3\n", "1 783 2\n", };
    std::string expected2 = "78321\n";
    biggestNumberTest(input2, expected2);

    TestInputType input5 = { "5\n", "2 4 5 2 10\n" };
    std::string expected5 = "542210\n";
    biggestNumberTest(input5, expected5);

    TestInputType input4 = { "2\n", "1000 4\n" };
    std::string expected4 = "41000\n";
    biggestNumberTest(input4, expected4);

    TestInputType input6 = { "2\n", "0 4\n" };
    std::string expected6 = "40\n";
    biggestNumberTest(input6, expected6);

/*
    TestInputType input6 = { "3\n", "2 10 3\n", "6\n", "0 0 0 20 4 2\n", };
    std::string expected6 = "3\n";
    biggestNumberTest(input6, expected6);

    TestInputType input7 = { "3\n", "1 1 1\n", "4\n", "0 0 0 0\n", };
    std::string expected7 = "0\n";
    biggestNumberTest(input7, expected7);
*/
}

using DataType = uint64_t;
using IterType = std::vector<DataType>::const_iterator;

const DataType powsOf10[] = { 1, 10, 100, 1000, 10000 };

int log10Int(const DataType number)
{
    return static_cast<int>(std::log10(static_cast<float>(number)));
}

void biggestNumberWrapper(std::istream& in, std::ostream& out)
{
    DataType n = 0, tmp = 0;
    in >> n;
    if (!n)
    {
        out << "0\n";
        return;
    }

    std::vector<DataType> numbers;
    numbers.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        in >> tmp;
        numbers.push_back(tmp);
    }

    std::sort(numbers.begin(), numbers.end(), [] (DataType lhs, DataType rhs) {
        DataType lgRhs = (rhs) ? log10Int(rhs) : 0;
        DataType lgLhs = (lhs) ? log10Int(lhs) : 0;
        DataType leftFirst = lhs * powsOf10[lgRhs + 1] + rhs;
        DataType rightFirst = rhs * powsOf10[lgLhs + 1] + lhs;
        return leftFirst > rightFirst;
    });

    for (DataType& n: numbers)
    {
        out << n;
    }

    out << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        biggestNumberTestWrapper();
    else
        biggestNumberWrapper(std::cin, std::cout);
    std::cout << "\n";
}
