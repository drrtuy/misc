#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <algorithm>

void theMostFreqWordWrapper(std::istream& in, std::ostream& out);

void theMostFreqWordTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    theMostFreqWordWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void theMostFreqWordTestWrapper()
{
    TestInputType input = { "5\ncaba\naba\ncaba\nabac\naba\n",};
    std::string expected = "aba\n";
    theMostFreqWordTest(input, expected);
    input.clear();
    expected.clear();

    input = { "3\nb\nbc\nbcd\n" };
    expected = "b\n";
    theMostFreqWordTest(input, expected);
    input.clear();
    expected.clear();

    input = { "10\nciwlaxtnhhrnenw\nciwnvsuni\nciwaxeujmsmvpojqjkxk\nciwnvsuni\nciwnvsuni\nciwuxlkecnofovq\nciwuxlkecnofovq\nciwodramivid\nciwlaxtnhhrnenw\nciwnvsuni\n" };
    expected = "ciwnvsuni\n";
    theMostFreqWordTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = uint64_t;
using Count = DataType;
using Word = std::string;
using WordList = std::vector<Word>;
using FreqMap = std::unordered_map<Word, Count>;

void theMostFreqWordWrapper(std::istream& in, std::ostream& out)
{
    size_t n;
    in >> n;
    std::string s1;
    FreqMap freqMap;
    freqMap.reserve(n); 

    for (size_t i = 0; i < n; ++i)
    {
        s1.clear();
        in >> s1;
        auto it = freqMap.find(s1);
        if (it != freqMap.end())
            freqMap[s1] += 1;
        else
            freqMap.insert({s1, 0});
    }

    if (n == 1)
    {
        out << s1 << "\n";
        return;
    }

    WordList wordList;
    size_t maxFreq = 0;
    for (auto freqMapIter = freqMap.begin(); freqMapIter != freqMap.end(); ++freqMapIter)
    {
        auto const &[k, v] = *freqMapIter;
        if (v > maxFreq)
        {
            maxFreq = v;
            wordList.clear();
            wordList.push_back(k);
        }
        else if (v == maxFreq)
            wordList.push_back(k);
    }
    std::sort(wordList.begin(), wordList.end(), std::less<std::string>());
    out << wordList[0] << "\n"; 
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        theMostFreqWordTestWrapper();
    else
        theMostFreqWordWrapper(std::cin, std::cout);
    std::cout << "\n";
}
