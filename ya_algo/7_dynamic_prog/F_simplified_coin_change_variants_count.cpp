#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

void coingChangeVariantsCountWrapper(std::istream& in, std::ostream& out);

void coingChangeVariantsCountTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    coingChangeVariantsCountWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void coingChangeVariantsCountTestWrapper()
{
    TestInputType input = { "6 3\n",};
    std::string expected = "13\n";
    coingChangeVariantsCountTest(input, expected);
    input.clear();
    expected.clear();

    input = { "7 7\n" };
    expected = "32\n";
    coingChangeVariantsCountTest(input, expected);
    input.clear();
    expected.clear();

    input = { "2 2\n" };
    expected = "1\n";
    coingChangeVariantsCountTest(input, expected);
    input.clear();
    expected.clear();

    input = { "1\n1\n" };
    expected = "0\n";
    coingChangeVariantsCountTest(input, expected);
    input.clear();
    expected.clear();

/*
    input = { "4\n20 21\n20 20\n21 21\n19 20" };
    expected = "4\n19 20\n20 20\n20 21\n21 21\n";
    coingChangeVariantsCountTest(input, expected);
    input.clear();
    expected.clear();
*/
}


using DataType = uint64_t;
using Dist = DataType;
using JumpDist = std::vector<Dist>;
using DPType = std::vector<DataType>;
static constexpr uint64_t divisor = 1000000007ULL;

void coingChangeVariantsCountWrapper(std::istream& in, std::ostream& out)
{
    DataType n;
    DataType k;
    in >> n;
    in >> k;

    DPType dp(n + 2, 0);
    dp[0] = 0;
    dp[1] = 0;
    for (size_t i = 2; i <= k + 1; ++i)
        dp[i] = 1;

    for (size_t i = 2; i <= n; ++i)
    {
        size_t limit = std::min(k, i);
        for (size_t j = limit; j > 0; --j)
            dp[i] = dp[i] % divisor + dp[i - j] % divisor;
    }
    out << dp[n] % divisor << std::endl;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        coingChangeVariantsCountTestWrapper();
    else
        coingChangeVariantsCountWrapper(std::cin, std::cout);
    std::cout << "\n";
}
