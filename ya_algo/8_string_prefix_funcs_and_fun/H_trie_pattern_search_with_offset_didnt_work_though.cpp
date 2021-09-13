#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <iterator>
#include <algorithm>

bool printed = false;

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
    TestInputType input = { "9\n3 9 1 2 5 10 9 1 7\n2\n4 10\n",};
    std::string expected = "1 8 \n";
    trieSearchTest(input, expected);
    input.clear();
    expected.clear();

    input = { "5\n1 2 3 4 5\n3\n10 11 12\n" };
    expected = "1 2 3 \n";
    trieSearchTest(input, expected);
    input.clear();
    expected.clear();

    input = { "50\n352 153 127 830 665 764 309 306 127 830 665 764 309 584 478 42 745 580 679 224 927 762 861 406 148 160 863 698 797 342 571 65 768 603 702 247 950 785 884 429 422 63 766 601 700 245 948 783 882 427\n5\n83 786 621 720 265\n" };
    expected = "3 9 16 20 26 32 36 42 46 \n";
    trieSearchTest(input, expected);
    input.clear();
    expected.clear();
}

class TrieNode;
using DataType = uint32_t;
using JumpKey = DataType;
using JumpType = std::unordered_map<JumpKey, TrieNode*, std::hash<JumpKey>>;
using HeapType = std::vector<DataType>;
using NeedleType = HeapType;
using NeedlesVector = std::vector<NeedleType>;
using OffsetType = int32_t;
using OffsetsVector = std::vector<OffsetType>;

class TrieNode
{
  public:
    void addNeedle(const NeedleType& needle)
    {
        auto current_node = this;
        for (auto number: needle)
        {
            auto jump = current_node->jumps.find(number);
            if (jump == jumps.end())
            {
                auto node = new TrieNode();
                current_node->jumps.insert({number, node});
                current_node = node;
            }
            else
                current_node = jump->second;
        }
    }

    TrieNode* jump(const JumpKey number)
    {
        auto jump = jumps.find(number);
        return (jump == jumps.end()) ? nullptr : jump->second;
    }

    bool isTerminal() const
    {
        return jumps.size() == 0;
    }

    JumpType jumps;
};

void generateNeedles(HeapType& heap, NeedleType& needle, OffsetsVector& needlesOffsets)
{
    auto heapSorted = heap; 
    auto needleSorted = needle; 
    std::sort(heapSorted.begin(), heapSorted.end(), std::less<DataType>());
    std::sort(needleSorted.begin(), needleSorted.end(), std::less<DataType>());
    auto heapSortedIt = heapSorted.begin();

    while (*heapSortedIt <= needleSorted[0] && heapSortedIt != heapSorted.end())
    {
        needlesOffsets.push_back(*heapSortedIt - needleSorted[0]);
        ++heapSortedIt;
    }
    // от min(needles) до max(needles) в heap 
    // от min(heap) до max(heap) в heap, если min(heap) > max(needle)
    while (heapSortedIt != heapSorted.end())
    {
        needlesOffsets.push_back(*heapSortedIt - needleSorted[0]);
        ++heapSortedIt;
    }
}

void trieSearchWrapper(std::istream& in, std::ostream& out)
{
    size_t n, m;
    DataType tmp;
    in >> n;
    HeapType heap;
    heap.reserve(n);
    for (size_t i = 0; i < n; ++i)
    {
        in >> tmp;
        heap.push_back(tmp);
    }

    in >> m;
    NeedleType needle;
    needle.reserve(m);
    for (size_t i = 0; i < m; ++i)
    {
        in >> tmp;
        needle.push_back(tmp);
    }

    OffsetsVector needlesOffsets;
    generateNeedles(heap, needle, needlesOffsets);
    TrieNode root;

    NeedleType generatedNeedle(needle.size(), 0);
    for (auto nOffset : needlesOffsets)
    {
        for (size_t i = 0; i < needle.size(); ++i)
            generatedNeedle[i] = needle[i] + nOffset;
        root.addNeedle(generatedNeedle);
    }
    // алгоритм поиска в trie
    for (size_t i = 0; i < heap.size(); ++i)
    {
        auto currentNode = &root;
        size_t offset = 0;
        bool needleMatchesSoFar = true;
        while (needleMatchesSoFar && (i + offset) < heap.size())
        {
            auto number = heap[i + offset];
            currentNode = currentNode->jump(number);
            if (currentNode != nullptr)
            {
                if (currentNode->isTerminal())
                    out << i + 1 << " ";
                ++offset;
            }
            else
                needleMatchesSoFar = false;
        }
    }
    out << "\n";
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
