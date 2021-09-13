#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <string_view>

void prefixGenerationCmpWrapper(std::istream& in, std::ostream& out);

void prefixGenerationCmpTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    prefixGenerationCmpWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void prefixGenerationCmpTestWrapper()
{
    TestInputType input = { "abracadabra\n",};
    std::string expected = "0 0 0 1 0 1 0 1 2 3 4 \n";
    prefixGenerationCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "xxzzxxz\n" };
    expected = "0 1 0 0 1 2 3 \n";
    prefixGenerationCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "aaaaa\n" };
    expected = "0 1 2 3 4 \n";
    prefixGenerationCmpTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = uint64_t;

void prefixGenerationCmpWrapper(std::istream& in, std::ostream& out)
{
    std::string s1;
    in >> s1;
    if (s1.empty() || s1.length() == 1)
        out << "0\n";

    std::vector<size_t> prefix(s1.length(), 0);
    size_t k = 0;
    for (size_t i = 1; i < s1.length(); ++i)
    {
        k = prefix[i-1];
        while (k > 0 && s1[k] != s1[i])
            k = prefix[k-1];
        if (s1[k] == s1[i])
            k += 1;
        prefix[i] = k;
    }
    for (auto p: prefix)
        out << p << " ";
    out << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        prefixGenerationCmpTestWrapper();
    else
        prefixGenerationCmpWrapper(std::cin, std::cout);
    std::cout << "\n";
}
