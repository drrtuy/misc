#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void cookiesWrapper(std::istream& in, std::ostream& out);

void cookiesTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    cookiesWrapper(in, ss);
    std::string out = ss.str();
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void cookiesTestWrapper()
{
    TestInputType input1 = { "2\n", "1 2\n", "3\n", "2 1 3\n", };
    std::string expected1 = "2\n";
    cookiesTest(input1, expected1);

    TestInputType input2 = { "3\n", "2 1 3\n", "2\n", "1 1\n", };
    std::string expected2 = "1\n";
    cookiesTest(input2, expected2);

    TestInputType input3 = { "0\n", "\n", "2\n", "1 1\n", };
    std::string expected3 = "0\n";
    cookiesTest(input3, expected3);

    TestInputType input4 = { "3\n", "2 1 3\n", "0\n", "\n", };
    std::string expected4 = "0\n";
    cookiesTest(input4, expected4);

    TestInputType input5 = { "3\n", "2 5 3\n", "1\n", "1\n", };
    std::string expected5 = "0\n";
    cookiesTest(input5, expected5);

    TestInputType input6 = { "3\n", "2 10 3\n", "6\n", "0 0 0 20 4 2\n", };
    std::string expected6 = "3\n";
    cookiesTest(input6, expected6);

    TestInputType input7 = { "3\n", "1 1 1\n", "4\n", "0 0 0 0\n", };
    std::string expected7 = "0\n";
    cookiesTest(input7, expected7);
}

using DataType = uint64_t;
using IterType = std::vector<DataType>::const_iterator;

void cookiesWrapper(std::istream& in, std::ostream& out)
{
    DataType n = 0, m = 0, tmp = 0;
    in >> n;
    if (!n)
    {
        out << "0\n";
        return;
    }

    std::vector<DataType> greedFactor;
    for(size_t i = 0; i < n; i++)
    {
        in >> tmp;
        greedFactor.push_back(tmp);
    }
    in >> m;
    if (!m)
    {
        out << "0\n";
        return;
    }

    std::vector<DataType> cookies; 
    for(size_t i = 0; i < m; i++)
    {
        in >> tmp;
        cookies.push_back(tmp);
    }
    std::sort(greedFactor.begin(), greedFactor.end(), std::less<DataType>());
    std::sort(cookies.begin(), cookies.end(), std::less<DataType>());
   
    size_t count = 0;
    IterType gfIter = greedFactor.begin();
    IterType cIter = cookies.begin();
    while (gfIter < greedFactor.end())
    {
        while (cIter < cookies.end() && *gfIter > *cIter)
        {
            ++cIter;
        }
        if (cIter < cookies.end() && *gfIter <= *cIter)
        {
            ++cIter;
            ++count;
            ++gfIter;
        }
        if (cIter == cookies.end())
            break;
    }

/*
    std::sort(greedFactor.begin(), greedFactor.end(), std::greater<DataType>());
    std::sort(cookies.begin(), cookies.end(), std::greater<DataType>());
   
    size_t count = 0;
    IterType gfIter = greedFactor.end();
    IterType cIter = cookies.end();
    while (gfIter <= greedFactor.begin())
    {
        while (cIter <= cookies.begin() && *gfIter > *cIter)
        {
            ++cIter;
        }
        if (cIter < cookies.end() && *gfIter <= *cIter)
        {
            ++count;
            ++gfIter;
        }
        if (cIter == cookies.end())
            break;
    }

*/
    out << count << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        cookiesTestWrapper();
    else
        cookiesWrapper(std::cin, std::cout);
    std::cout << "\n";
}
