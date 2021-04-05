#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <cmath>

void bubbleWrapper(std::istream& in, std::ostream& out);

void bubbleTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    bubbleWrapper(in, ss);
    std::string out = ss.str();
    std::cout << "result " << out;
    std::cout << "expected " << expected;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void bubbleTestWrapper()
{
    TestInputType input1 = { "5\n", "4 3 9 2 1\n", };
    std::string expected1 = "3 4 2 1 9 \n3 2 1 4 9 \n2 1 3 4 9 \n1 2 3 4 9 \n";
    bubbleTest(input1, expected1);

    TestInputType input2 = { "5\n", "12 8 9 10 11\n",};
    std::string expected2 = "8 9 10 11 12 \n";
    bubbleTest(input2, expected2);

    TestInputType input5 = { "5\n", "5 4 3 2 1\n" };
    std::string expected5 = "4 3 2 1 5 \n3 2 1 4 5 \n2 1 3 4 5 \n1 2 3 4 5 \n";
    bubbleTest(input5, expected5);

    TestInputType input3 = { "5\n", "8 9 10 11 12\n",};
    std::string expected3 = "8 9 10 11 12 \n";
    bubbleTest(input3, expected3);


/*
    TestInputType input6 = { "2\n", "0 4\n" };
    std::string expected6 = "40\n";
    bubbleTest(input6, expected6);
*/
}

using DataType = int64_t;
using IterType = std::vector<DataType>::const_iterator;

void bubbleWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0;
    DataType tmp = 0;
    std::string line1;
    std::stringstream ssin;
    std::getline(in, line1);
    ssin << line1;
    ssin >> n;

    std::vector<DataType> data;
    data.reserve(n);
    std::string arrayStr;
    std::getline(in, arrayStr);
    ssin.clear();
    ssin << arrayStr;
    for(size_t i = 0; i < n; i++)
    {
        ssin >> tmp;
        data.push_back(tmp);
    }

    bool isSorted = false;
    size_t i = 1;
    for (; !isSorted && i < n; ++i)
    {
        isSorted = true;
        for (size_t it = 0; it < n - i; ++it)
        {
            size_t nextIdx = it + 1;
            if (data[it] > data[nextIdx])
            {
                size_t buf = data[it];
                data[it] = data[nextIdx];
                data[nextIdx] = buf;
                isSorted = false;
            }
        }

        if (!isSorted)
        {
            for (auto e: data)
                out << e << " ";
            out << "\n";
        }
        if (isSorted)
            break;
    }
    // Sorted on the last loop
    // or was originally sorted
    if ((!isSorted && i == n - 1) || (isSorted && i == 1))
    {
        for (auto e: data)
            out << e << " ";
        out << "\n";
    }

}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        bubbleTestWrapper();
    else
        bubbleWrapper(std::cin, std::cout);
    std::cout << "\n";
}
