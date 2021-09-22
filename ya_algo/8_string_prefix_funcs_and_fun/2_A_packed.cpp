#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stack>

void packedStringCmpWrapper(std::istream& in, std::ostream& out);

void packedStringCmpTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    packedStringCmpWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void packedStringCmpTestWrapper()
{
    TestInputType input = { "3\n2[a]2[ab]\n3[a]2[r2[t]]\na2[aa3[b]]\n",};
    std::string expected = "aaa\n";
    packedStringCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "3\nabacabaca\n2[abac]a\n3[aba]\n" };
    expected = "aba\n";
    packedStringCmpTest(input, expected);
    input.clear();
    expected.clear();
}

using WordType = std::string;
using DictType = std::vector<WordType>;
using SymbType = char;

// Оставил в public только то, что надо.
class PackedWordDecompressorHelper: private std::stack<SymbType>
{
  public:
    using std::stack<SymbType>::top;
    using std::stack<SymbType>::pop;
    using std::stack<SymbType>::push;
    using std::stack<SymbType>::empty;
    
    const SymbType popTop()
    {
        const SymbType topElement = top();
        pop();
        return topElement;
    }

    void pushWord(const WordType& word)
    {
        for(auto el: word)
            push(el);
    }
    
    WordType getDecompressedWord()
    {
        WordType result;
        result.reserve(size());
        while(!empty())
            result.insert(result.begin(), popTop());
        return result;
    }
};


WordType decompress(const WordType& compressedString)
{
    PackedWordDecompressorHelper helper;
    size_t multiplier;
    for (auto symb : compressedString)
    {
        //std::cout << "dec reading char from input str " << symb << "\n";
        if (symb == ']')
        {
            //std::cout << "dec read ] " << symb << "\n";
            WordType multiSubWord;
            WordType numberAsStr;
            char subSymb = helper.popTop();
            while (subSymb != '[')
            {
                multiSubWord.insert(multiSubWord.begin(), subSymb);
                subSymb = helper.popTop();
            }
            //std::cout << "dec read [" << multiSubWord << "]" << "\n";
            subSymb = helper.top();
            while (std::isdigit(subSymb))
            {
                numberAsStr.insert(numberAsStr.begin(), subSymb);
                helper.pop();
                if (helper.empty())
                    break;
                subSymb = helper.top();
            }

            //std::cout << "dec read numberAsStr " << numberAsStr << "\n";
            multiplier = std::stoi(numberAsStr);
            //std::cout << "dec read multiplier " << multiplier << "\n";

            for (size_t i = 0; i < multiplier; ++i)
                helper.pushWord(multiSubWord);
        }
        else
            helper.push(symb);
    }
    std::string res = helper.getDecompressedWord();
    //std::cout << "decompr result " << res << "\n";
    return res;
}

// Расстояние общей части для двух пар итераторов.
// Попробовать string_view, если не хватит времени.
template<class I> auto commonPartLength(I abegin, I aend, I bbegin, I bend)
{
    return std::distance(abegin, std::mismatch(abegin, aend, bbegin, bend).first);
} 

WordType pickMinPrefix(const WordType& x, const WordType& y)
{
    auto commonPrefixLength = commonPartLength(x.begin(), x.end(), y.begin(), y.end());
    return std::string(x, 0, commonPrefixLength);
}

void packedStringCmpWrapper(std::istream& in, std::ostream& out)
{
    size_t n;
    in >> n;
    WordType tmp;
    DictType dict;
    dict.reserve(n);
    for (size_t i = 0; i < n; ++i)
    {
        in >> tmp;
        dict.push_back(std::move(decompress(tmp)));
    }

    std::sort(dict.begin(), dict.end(), std::less<WordType>());
    WordType minPrefix(std::move(dict[0]));
    for (size_t i = 1; i < dict.size(); ++i)
        minPrefix = std::move(pickMinPrefix(minPrefix, dict[i]));    

    out << minPrefix << "\n";
}

int main(int argc, char** argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        packedStringCmpTestWrapper();
    else
        packedStringCmpWrapper(std::cin, std::cout);
    std::cout << "\n";
}
