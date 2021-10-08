// 53964835
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <deque>

// Алгоритм: разжимаем строки с помощью стэковой машины, складывая в массив.
// Сортируем строки, берём самую короткую как исходный минимальный префикс,
// проходим по расжатым строкам, примеряя текущий минимальный префикс к очередной строке.
// Сложность по времени O(N * M), где N - кол-во слов, а M - длина самого короткого расжатого слова.
// Сложность по памяти O(P), где P - суммарная длина слов после декомпрессии.

// От рекомендаций получил значительный профит: время исполнение в два раза меньше в пике,
// а потребление памяти в 10.

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
using SymbType = char;

class PackedWordDecompressorHelper: private std::deque<SymbType>
{
  public:
    using std::deque<SymbType>::back;
    using std::deque<SymbType>::pop_back;
    using std::deque<SymbType>::push_back;
    using std::deque<SymbType>::pop_front;
    using std::deque<SymbType>::empty;
    using std::deque<SymbType>::size;

    const SymbType popTop()
    {
        const SymbType topElement = back();
        pop_back();
        return topElement;
    }

    void pushWord(const WordType& word)
    {
        for(auto el: word)
            push_back(el);
    }

    WordType getDecompressedWord()
    {
        WordType result;
        result.reserve(size());
        while(!empty())
        {
            result.push_back(front());
            pop_front();
        }
        return result;
    }
};

// Простой парсер со стековой машиной на базе dequeu.
// Второй аргумент позволяет декодить не более чем resultWordMaxLength символов.
WordType decompress(const WordType& compressedString, const size_t resultWordMaxLength)
{
    PackedWordDecompressorHelper helper;
    size_t multiplier;
    size_t parentesisCounter = 0;
    for (auto symb : compressedString)
    {
        if (symb == ']')
        {
            --parentesisCounter;
            WordType multiSubWord;
            WordType numberAsStr;
            char subSymb = helper.popTop();
            while (subSymb != '[')
            {
                multiSubWord.insert(multiSubWord.begin(), subSymb);
                subSymb = helper.popTop();
            }
            subSymb = helper.back();
            while (std::isdigit(subSymb))
            {
                numberAsStr.insert(numberAsStr.begin(), subSymb);
                helper.pop_back();
                if (helper.empty())
                    break;
                subSymb = helper.back();
            }

            multiplier = std::stoi(numberAsStr);

            for (size_t i = 0; i < multiplier; ++i)
                helper.pushWord(multiSubWord);
        }
        else
        {
            if (symb == '[')
                ++parentesisCounter;
            helper.push_back(symb);
        }
        if (helper.size() > resultWordMaxLength && parentesisCounter == 0)
            return helper.getDecompressedWord();
    }
    return helper.getDecompressedWord();
}

// Расстояние общей части для двух пар итераторов.
template<class I> auto commonPartLength(I abegin, I aend, I bbegin, I bend)
{
    return std::distance(abegin, std::mismatch(abegin, aend, bbegin, bend).first);
}

// Возвращаем общий префикс для двух строк.
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
    in >> tmp;
    WordType minPrefix(std::move(decompress(tmp, std::numeric_limits<size_t>::max())));
    for (size_t i = 1; i < n; ++i)
    {
        in >> tmp;
        minPrefix = std::move(pickMinPrefix(minPrefix, decompress(tmp, minPrefix.length()))); 
    }

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
