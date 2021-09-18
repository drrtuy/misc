#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <set>

void coinChangeVariantsWrapper(std::istream& in, std::ostream& out);

void coinChangeVariantsTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    coinChangeVariantsWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void coinChangeVariantsTestWrapper()
{
    TestInputType input = { "5\n3\n3 2 1\n",};
    std::string expected = "5\n";
    coinChangeVariantsTest(input, expected);
    input.clear();
    expected.clear();

    input = { "3\n2\n2 1\n" };
    expected = "2\n";
    coinChangeVariantsTest(input, expected);
    input.clear();
    expected.clear();

    input = { "8\n1\n5\n" };
    expected = "0\n";
    coinChangeVariantsTest(input, expected);
    input.clear();
    expected.clear();

/*
    input = { "4\n20 21\n20 20\n21 21\n19 20" };
    expected = "4\n19 20\n20 20\n20 21\n21 21\n";
    coinChangeVariantsTest(input, expected);
    input.clear();
    expected.clear();
*/
}


using DataType = int64_t;
using Nominal = DataType;
using CoinsSet = std::set<Nominal, std::greater<Nominal>>;
using Coins = std::vector<Nominal>;
using DPType = std::vector<std::vector<Nominal>>;

void printOutMatrix(DPType& dp)
{
    std::cout << "dp\n";
    for (auto& row: dp)
    {
        std::copy(row.begin(), row.end(), std::ostream_iterator<DataType>(std::cout, " "));
        std::cout << "\n";
    }
    std::cout << "\n";
}

DataType coinChangeVariants(Coins& coins, Nominal X)
{
    DPType dp(X + 1, std::vector<DataType>(coins.size(), 0));
    std::fill(dp[0].begin(), dp[0].end(), 1);

    for (DataType i = 1; i <= X; ++i)
    {
        for (DataType j = 0; (size_t)j < coins.size(); ++j)
        {
            DataType numberWithNthCoin = i - coins[j] >= 0 ? dp[i - coins[j]][j] : 0;
            DataType numberWONthCoin = j >= 1 ? dp[i][j - 1] : 0;
            dp[i][j] = numberWithNthCoin + numberWONthCoin;
//            printOutMatrix(dp);
        }
    }
    return dp[X][coins.size()-1];
}

void coinChangeVariantsWrapper(std::istream& in, std::ostream& out)
{
    DataType X;
    DataType k;
    Nominal tmp;
    in >> X;
    in >> k;

    CoinsSet coinsSet;
    for (DataType i = 0; i < k; ++i)
    {
        in >> tmp;
        coinsSet.insert(tmp);
    }
    Coins coins(coinsSet.begin(), coinsSet.end());
    if (coins.size() == 1)
    {
        if (X % coins[0])
            out << 0 << std::endl;
        else
            out << X / coins[0] << std::endl;
    }
    else
        out << coinChangeVariants(coins, X) << std::endl;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        coinChangeVariantsTestWrapper();
    else
        coinChangeVariantsWrapper(std::cin, std::cout);
    std::cout << "\n";
}
