// 52487045
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

// Если полусумма чётная, то задача сводится к coin change problem с
// ограниченным кол-вом монет, где в кач-ве целевой суммы выступает полусумма,
// а монеты - кол-во очков.
// В DP хранится признак получения кол-ва очков равного индексу с помощью
// какого-то подмножества очков.
// dp заполняем проходя во внешнем цикле по массиву полученных очков, а во внутреннем от нужной полусуммы до 1. 
// Переход описан в тексте.
// Сложность по времени O(n * sum / 2), по памяти max(O(n), O(sum/2)) 

void coinChangeCountWrapper(std::istream& in, std::ostream& out);

void coinChangeCountTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    coinChangeCountWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void coinChangeCountTestWrapper()
{
    TestInputType input = { "4\n1 5 7 1\n",};
    std::string expected = "True\n";
    coinChangeCountTest(input, expected);
    input.clear();
    expected.clear();

    input = { "3\n2 10 9\n" };
    expected = "False\n";
    coinChangeCountTest(input, expected);
    input.clear();
    expected.clear();

    input = { "6\n7 9 3 4 6 7\n" };
    expected = "True\n"; coinChangeCountTest(input, expected); input.clear();
    expected.clear();

    input = { "2\n1 9\n" };
    expected = "False\n";
    coinChangeCountTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = int64_t;
using Nominal = DataType;
using Scores = std::vector<Nominal>;
using DPType = std::vector<bool>;

void coinChangeCountWrapper(std::istream& in, std::ostream& out)
{
    DataType n;
    Nominal tmp;
    in >> n;
    Scores scores;
    Nominal sum = 0;
    for (int i = 0; i < n; ++i)
    {
        in >> tmp;
        scores.push_back(tmp);
        sum += tmp;
    }
   
    if (sum % 2 || scores.size() == 1)
    {
        out << "False\n";
        return;
    }
    Nominal target = sum / 2;
    DPType dp(target + 1, false);

    for (auto score: scores)
    {
        // Чтобы избежать переиспользование комплимента, проходим от полусуммы до 0.
        // Можно и до min(scores), но придётся искать минимум.
        for (int i = target; i >= 1; --i)
        {
            // Если комплимент(кол-во очков) дополняет до i или i = кол-во очков
            // или i уже можно достигнуть суммой какого-то подмножества.
            if ((i - score > 0 && dp[i - score]) || score == i || dp[i])
                dp[i] = true;
        }

    }
    if (dp[target])
        out << "True\n";
    else
        out << "False\n";
 }

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        coinChangeCountTestWrapper();
    else
        coinChangeCountWrapper(std::cin, std::cout);
    std::cout << "\n";
}
