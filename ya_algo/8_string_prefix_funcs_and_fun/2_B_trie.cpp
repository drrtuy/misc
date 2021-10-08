// 53950074
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <array>

// Для решения используется одномерная динамика + trie. В dp массив bool,
// указывающих можно ли достигнуть символа проверяемой строки. База динамики - dp[0] = true.
// Индукция dp[i] = isTerminal(i + offset) ? true : false.
// Проходим по символам проверяемой строки, взводим bool в dp[i], если символ можно достигнуть и он
// терминальный в trie. В dp.back() получаем ответ можно ли разобрать строку на шаблоны или нет.
// Сложность по времени O(len(пров. строка) + sum(len(шаблон_i)), где i - номер шаблона.
// Сложность по памяти в худшем случае O(len(пров. строка) + len(массива шаблонов) * размер алфавита.
// в среднем меньше из-за совпадения символов в шаблонах.

void trieSearchWrapper(std::istream& in, std::ostream& out);

void trieSearchTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    trieSearchWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void trieSearchTestWrapper()
{
    TestInputType input = { "examiwillpasstheexam\n5\nwill\npass\nthe\nexam\ni\n",};
    std::string expected = "YES\n";
    trieSearchTest(input, expected);
    input.clear();
    expected.clear();

    input = { "abacaba\n2\nabac\ncaba\n" };
    expected = "NO\n";
    trieSearchTest(input, expected);
    input.clear();
    expected.clear();

    input = { "abacaba\n3\nabac\ncaba\naba\n" };
    expected = "YES\n";
    trieSearchTest(input, expected);
    input.clear();
    expected.clear();

    input = { "sscevscescescscsscevscevscesscsc\n4\nsce\ns\nscev\nsc\n" };
    expected = "YES\n";
    trieSearchTest(input, expected);
    input.clear();
    expected.clear();
}

class TrieNode;
using DataType = uint32_t;
using JumpKey = char;
// Замена на вектор фиксированной длины привела к увеличению потребления памяти и снижению времени исполнения,
// примерно в одинаковых пропорциях, так что здесь trade-off, где надо осознанно выбирать.
constexpr size_t AlphaSize = 26;
using JumpType = std::array<TrieNode*, AlphaSize>;
using HeapType = std::string;
using NeedleType = HeapType;
using DynamicType = std::vector<bool>;

class TrieNode
{
  public:
    TrieNode() : mIsTerminal(false)
    {
        jumps.fill(nullptr);
    };
    void addNeedle(const NeedleType& needle)
    {
        auto currentNode = this;
        for (auto symbol: needle)
        {
            assert('a' <= symbol && symbol <= 'z');
            size_t jumpTableIdx = symbol - 'a';
            auto jump = currentNode->jumps[jumpTableIdx];
            if (jump == nullptr)
            {
                auto node = new TrieNode();
                currentNode->jumps[jumpTableIdx] = node;
                currentNode = node;
            }
            else
                currentNode = jump;
        }
        currentNode->mIsTerminal = true;
    }

    TrieNode* jump(const JumpKey symbol)
    {
        assert('a' <= symbol && symbol <= 'z');
        size_t jumpTableIdx = symbol - 'a';
        return jumps[jumpTableIdx];
    }

    bool isTerminal() const
    {
        return mIsTerminal;
    }

    bool hasJumpTable() const
    {
        return jumps.size() > 0;
    }

 private:
    bool mIsTerminal;
    JumpType jumps;
};

void trieSearchWrapper(std::istream& in, std::ostream& out)
{
    HeapType heap;
    in >> heap;
    DataType tmp;
    DynamicType dp(heap.length() + 1, false);
    dp[0] = true;

    TrieNode root;
    NeedleType needle;
    in >> tmp;
    for (size_t i = 0; i < tmp; ++i)
    {
        in >> needle;
        root.addNeedle(needle);
    }

    // алгоритм поиска в trie
    for (size_t i = 0; i < heap.size(); ++i)
    {
        if (!dp[i])
            continue;
        auto currentNode = &root;
        size_t offset = 0;
        while (currentNode != nullptr && (i + offset) < heap.size())
        {
            auto symbol = heap[i + offset++];
            currentNode = currentNode->jump(symbol);
            if (currentNode != nullptr && currentNode->isTerminal())
                dp[i + offset] = true;
        }
    }
    if (dp.back())
        out << "YES\n";
    else
        out << "NO\n";
}

int main(int argc, char** argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        trieSearchTestWrapper();
    else
        trieSearchWrapper(std::cin, std::cout);
    std::cout << "\n";
}
