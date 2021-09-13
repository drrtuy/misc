#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

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
using HeapType = std::vector<DataType>;
using NeedleType = HeapType;
using NeedlesVector = std::vector<NeedleType>;
using OffsetType = int32_t;
using OffsetsVector = std::vector<OffsetType>;

void trieSearchWrapper(std::istream& in, std::ostream& out)
{
    size_t n, m;
    DataType tmp, tmpPrev;
    in >> n;
    OffsetsVector heap;
    heap.reserve(n);
    in >> tmpPrev;
    for (size_t i = 1; i < n; ++i)
    {
        in >> tmp;
        heap.push_back((OffsetType)(tmp - tmpPrev));
        tmpPrev = tmp;
    }

    in >> m;
    OffsetsVector needle;
    needle.reserve(m);
    in >> tmpPrev;
    for (size_t i = 1; i < m; ++i)
    {
        in >> tmp;
        needle.push_back((OffsetType)(tmp - tmpPrev));
        tmpPrev = tmp;
    }
    size_t patternSize = needle.size();
    needle.push_back(0x7FFFFFFF);
/*
    std::cout << "needle ";
    for (auto el: needle)
        std::cout << el << " ";
    std::cout << "\n";
*/
    heap.insert(heap.begin(), needle.begin(), needle.end());
/*
    std::cout << "heap ";
    for (auto el: heap)
        std::cout << el << " ";
    std::cout << "\n";
*/

    std::vector<size_t> prefix(heap.size(), 0);
    size_t k = 0, prevP = 0;
    std::vector<size_t> results;
    for (size_t i = 1; i < heap.size(); ++i)
    {
        k = prevP;
        while (k > 0 && heap[k] != heap[i])
            k = prefix[k-1];
        if (heap[k] == heap[i])
            k += 1;
        if (i < patternSize)
            prefix[i] = k;
        prevP = k;
        if (k == patternSize)
        {
            results.push_back(i - 2 * patternSize + 1); 
        }
    }
/*
    std::cout << "prefix \n";
    for (auto el : prefix)
        std::cout << el << " ";


    std::cout << "result \n";
    for (auto el : results)
        std::cout << el << " ";
*/
    for (auto el: results)
        out << el << " ";
    out << "\n";
/*
    size_t n, m;
    DataType tmp, tmpPrev;
    in >> n;
    std::stringstream ss;
    ss << "#";
    in >> tmpPrev;
    for (size_t i = 1; i < n; ++i)
    {
        in >> tmp;
        if (i + 1 < n)
            ss << (OffsetType)(tmp - tmpPrev) << " ";
        else
            ss << (OffsetType)(tmp - tmpPrev);
        tmpPrev = tmp;
    }

    std::string heapString = std::move(ss.str());
    ss.str("");

    in >> m;
    in >> tmpPrev;
    for (size_t i = 1; i < m; ++i)
    {
        in >> tmp;
        if (i + 1 < m)
            ss << (OffsetType)(tmp - tmpPrev) << " ";
        else
            ss << (OffsetType)(tmp - tmpPrev);
        tmpPrev = tmp;
    }

    std::string needleString = std::move(ss.str());
    size_t patternLength = needleString.length();

    std::cout << "heap " << heapString << "\n";
    std::cout << "needle " << needleString << "\n";

    needleString += heapString;

    std::cout << "combination " << needleString << "\n"; 

    std::vector<size_t> prefix(needleString.length(), 0);
    size_t k = 0;
    std::vector<size_t> results;
    for (size_t i = 1; i < needleString.length(); ++i)
    {
        k = prefix[i-1];
        while (k > 0 && needleString[k] != needleString[i])
            k = prefix[k-1];
        if (needleString[k] == needleString[i])
            k += 1;
        if (i < needleString.length())
            prefix[i] = k;
        if (k == patternLength)
        {
            std::cout << "k " << k << "\n";
            results.push_back(i - 2 * patternLength); 
        }
    }

    std::cout << "prefix \n";
    for (auto el : prefix)
        std::cout << el << " ";


    std::cout << "result \n";
    for (auto el : results)
        std::cout << el << " ";

    out << "\n";
*/
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
