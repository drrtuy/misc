#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <unordered_map>

// Задача решается созданием trie из списка данных шаблонов и последующего прохода
// по исходной строке. В строке ищем шаблон максимальной длины из данных.

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

    input = { "wwwfc3\nc\nw\nww\nwwf\n" };
    expected = "YES\n";
    trieSearchTest(input, expected);
    input.clear();
    expected.clear();
}

class TrieNode;
using DataType = uint32_t;
using JumpKey = char;
using JumpType = std::unordered_map<JumpKey, TrieNode*, std::hash<JumpKey>>;
using HeapType = std::string;
using NeedleType = HeapType;
using NeedlesVector = std::vector<NeedleType>;

class TrieNode
{
  public:
    TrieNode() : mIsTerminal(false) {};
    void addNeedle(const NeedleType& needle)
    {
        auto currentNode = this;
        for (auto symbol: needle)
        {
            auto jump = currentNode->jumps.find(symbol);
            if (jump == jumps.end())
            {
                auto node = new TrieNode();
                currentNode->jumps.insert({symbol, node});
                currentNode = node;
            }
            else
                currentNode = jump->second;
        }
        currentNode->mIsTerminal = true;
    }

    TrieNode* jump(const JumpKey symbol)
    {
        auto jump = jumps.find(symbol);
        return (jump == jumps.end()) ? nullptr : jump->second;
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

    TrieNode root;
    NeedleType needle;
    in >> tmp;
    // Строим trie
    for (size_t i = 0; i < tmp; ++i)
    {
        in >> needle;
        root.addNeedle(needle);
    }

    bool needleMatchesSoFar = true;
    bool foundAtLeastOne = false;
    // алгоритм поиска в trie
    // Ищем совпадающий needle максимальной длины.
    for (size_t i = 0; i < heap.size();)
    {
        foundAtLeastOne = false;
        auto currentNode = &root;
        size_t offset = 0;
        std::vector<DataType> foundTerminalPositions;
        while (needleMatchesSoFar && (i + offset) < heap.size())
        {
            std::cout << "trying i " << i << " i+offset " << (int)i+offset-1 << " " << std::string(heap, i, offset) << "\n";
            auto symbol = heap[i + offset];
            currentNode = currentNode->jump(symbol);
            if (currentNode != nullptr)
            {
                ++offset;
                if (currentNode->isTerminal())
                {
                    foundAtLeastOne = true;
                    foundTerminalPositions.push_back(offset);
                    std::cout << "isTerminal i " << i << " i+offset " << (int)i+offset-1 << " " << std::string(heap, i, offset) << "\n";
                    if (!currentNode->hasJumpTable()) // Это leaf trie - досрочно выходим из inner loop.
                    {
                        std::cout << "isFinalTerminal i " << i << " i+offset " << (int)i+offset-1 << " " << std::string(heap, i, offset) << "\n";
                        break;
                    }
                }
            }
            else
            {
                if (!foundAtLeastOne)
                {
                    std::cout << "failed pattern search in trie i " << i << " i+offset " << (int)i+offset-1 << " " << std::string(heap, i, offset) << "\n";
                    needleMatchesSoFar = false; // Не найден ни  один шаблон и нет перехода по симвволу в trie.
                }
                else
                {
                    std::cout << "fallback to the prev result in trie i " << i << " i+offset " << (int)i+offset-1 << " " << std::string(heap, i, offset) << "\n";
                    break; // Нет перехода по символу, но было найдено совпадение меньшей длины. Прерываем inner loop.
                }
            }
        }
        i += offset;
        if (!needleMatchesSoFar || (i >= heap.size() && !currentNode->isTerminal()))
        {
            needleMatchesSoFar = false;
            break;
        }
    }
    if (needleMatchesSoFar)
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
