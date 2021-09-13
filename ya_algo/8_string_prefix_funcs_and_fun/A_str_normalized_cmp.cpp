#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void normCmpWrapper(std::istream& in, std::ostream& out);

void normCmpTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    normCmpWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void normCmpTestWrapper()
{
    TestInputType input = { "mxyskaoghi\nqodfrgmslc\n",};
    std::string expected = "YES\n";
    normCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "agg\nxdd\n" };
    expected = "YES\n";
    normCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "agg\nxda\n" };
    expected = "NO\n";
    normCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "aba\nxxx\n" };
    expected = "NO\n";
    normCmpTest(input, expected);
    input.clear();
    expected.clear();
}


using DataType = uint64_t;
using Dict = std::vector<char>;

void normCmpWrapper(std::istream& in, std::ostream& out)
{
    std::string s1, s2;
    in >> s1;
    in >> s2;
    if (s1.length() != s2.length())
    {
        out << "NO\n";
        return;
    }
    Dict d(256, 0);
    Dict s2CharsUsageCounter(256, 0);
    for (size_t i = 0; i < s1.length(); ++i)
    {
        if (!d[s1[i]])
        {
            char c = s2[i];
            if (!s2CharsUsageCounter[c])
                s2CharsUsageCounter[c] = 1;
            else
            {
                out << "NO\n";
                return;
            }
            d[s1[i]] = c;
        }
        else if (d[s1[i]] != s2[i])
        {
            out << "NO\n";
            return;
        }
    }
    out << "YES\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        normCmpTestWrapper();
    else
        normCmpWrapper(std::cin, std::cout);
    std::cout << "\n";
}
