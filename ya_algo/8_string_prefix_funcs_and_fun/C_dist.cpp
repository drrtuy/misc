#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <string_view>

void levenstheinDistWrapper(std::istream& in, std::ostream& out);

void levenstheinDistTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    levenstheinDistWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void levenstheinDistTestWrapper()
{
    TestInputType input = { "abcdefg\nabdefg\n",};
    std::string expected = "OK\n";
    levenstheinDistTest(input, expected);
    input.clear();
    expected.clear();

    input = { "helo\nhello\n" };
    expected = "OK\n";
    levenstheinDistTest(input, expected);
    input.clear();
    expected.clear();

    input = { "dog\nfog\n" };
    expected = "OK\n";
    levenstheinDistTest(input, expected);
    input.clear();
    expected.clear();

    input = { "mama\npapa\n" };
    expected = "FAIL\n";
    levenstheinDistTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = uint64_t;
using Distance = uint64_t;

// Расстояние общей части для двух пар итераторов.
template<class I> auto commonPartLength(I abegin, I aend, I bbegin, I bend)
{
    return std::distance(abegin, std::mismatch(abegin, aend, bbegin, bend).first);
} 

// Маскируем в string_view общие префиксы и суффиксы.
static inline void dropCommonPrefixAndSuffix(std::string_view& a, std::string_view& b)
{
	auto prefix = commonPartLength(a.begin(), a.end(), b.begin(), b.end());
	a.remove_prefix(prefix);
	b.remove_prefix(prefix);

    auto suffix = commonPartLength(a.rbegin(), a.rend(), b.rbegin(), b.rend());
	a.remove_suffix(suffix);
    b.remove_suffix(suffix);
} 

void levenstheinDistWrapper(std::istream& in, std::ostream& out)
{
    std::string s1, s2;
    in >> s1;
    in >> s2;
    if (abs(s1.length() - s2.length()) > 1)
    {
        out << "FAIL\n";
        return;
    }

    std::string_view a(s1);
    std::string_view b(s2);
    if (a.length() > b.length()) std::swap(a,b);
    dropCommonPrefixAndSuffix(a, b);

    size_t maxPrefixLength = std::max(a.length(), b.length());
    if (maxPrefixLength > 1)
        out << "FAIL\n";
    else
        out << "OK\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        levenstheinDistTestWrapper();
    else
        levenstheinDistWrapper(std::cin, std::cout);
    std::cout << "\n";
}
