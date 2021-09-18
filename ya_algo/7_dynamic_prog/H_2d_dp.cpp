#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <iterator>

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
    TestInputType input = { "2 3\n101\n110\n",};
    std::string expected = "3\n";
    coinChangeVariantsTest(input, expected);
    input.clear();
    expected.clear();

    input = { "3 3\n100\n110\n001\n" };
    expected = "2\n";
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

using DataType = uint64_t;
using FlowerNumber = DataType; 
using DPType = std::vector<std::vector<FlowerNumber>>;
using CellType = uint8_t;
using MazeType = std::vector<std::vector<CellType>>;

template <typename M, typename T>
void printOutMatrix(M& dp)
{
    std::cout << "matrix\n";
    for (auto& row: dp)
    {
        for (auto el: row)
            std::cout << std::to_string(el);
        std::cout << "\n";
    }
    std::cout << "\n";
}

void coinChangeVariantsWrapper(std::istream& in, std::ostream& out)
{
    DataType n;
    DataType m;
    char tmp;
    in >> n;
    in >> m;
    MazeType maze(n, std::vector<CellType>(m, 0));

    for (DataType i = n; i > 0; --i)
    {
        for (DataType j = 0; j < m; ++j)
        {
            in >> tmp;
            maze[i-1][j] = tmp - '0';
        }
    }
    //printOutMatrix<MazeType, CellType>(maze);

    DPType dp(n + 1, std::vector<FlowerNumber>(m + 1, 0));
    dp[1][1] += maze[0][0];
    for (size_t i = 1; i <= n; ++i)
    {
        for (size_t j = 1; j <= m; ++j)
            dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]) + maze[i-1][j-1];
    }
    out << dp[n][m] << std::endl;
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
