#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <string_view>

void strangeStrCmpWrapper(std::istream& in, std::ostream& out);

void strangeStrCmpTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    strangeStrCmpWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void strangeStrCmpTestWrapper()
{
    TestInputType input = { "ccccz\naaaaaz\n",};
    std::string expected = "0\n";
    strangeStrCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "gggggbbb\nbbef\n" };
    expected = "-1\n";
    strangeStrCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "z\naaaaaaa\n" };
    expected = "1\n";
    strangeStrCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "bb\ncccbaaba\n" };
    expected = "0\n";
    strangeStrCmpTest(input, expected);
    input.clear();
    expected.clear();

    input = { "mcgfkwueimuiaukecyskakeyiooueuesiu\nfiogaoweaywukcwcuuq\n" };
    expected = "0\n";
    strangeStrCmpTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = uint64_t;
constexpr const char aSymb = 'a';

template<class T>
bool validSymbAreInLeftover(T& iter, const T& end)
{
    size_t validSymbolsInLeftOver = 0;
    while (iter != end)
    {
        auto code = *iter;
        //std::cout << "codeS2 " << code << "\n";
        validSymbolsInLeftOver += (code % 2 != 0) ? 0 : 1;
        ++iter;
    }
    return validSymbolsInLeftOver > 0;
}

void strangeStrCmpWrapper(std::istream& in, std::ostream& out)
{
    std::string s1, s2;
    in >> s1;
    in >> s2;

    auto s1I = s1.begin();
    auto s2I = s2.begin();
    uint8_t codeS1 = *s1I;
    uint8_t codeS2 = *s2I;
    size_t eqCounter = 0;
    while (s1I != s1.end() || s2I != s2.end())
    {
        //std::cout << "codeS1 " << codeS1 << " codeS2 " << codeS2 << "\n";
        while (s1I != s1.end() && codeS1 % 2 != 0)
        {
            ++s1I;
            if (s1I != s1.end())
                codeS1 = *s1I;
            //std::cout << "codeS1 " << codeS1 << "\n";
        }

        while (s2I != s2.end() && codeS2 % 2 != 0)
        {
            ++s2I;
            if (s2I != s2.end())
                codeS2 = *s2I;
            //std::cout << "codeS2 " << codeS2 << "\n";
        }

        if (s1I == s1.end() && s2I == s2.end())
        {
            out << "0\n";
            return;
        }
        else if (s1I == s1.end() && s2I != s2.end())
        {
            if (validSymbAreInLeftover(s2I, s2.end()))
                out << "-1\n";
            else
                out << "0\n";
            return;
        }
        else if (s1I != s1.end() && s2I == s2.end())
        {
            if (validSymbAreInLeftover(s1I, s1.end()))
                out << "1\n";
            else
                out << "0\n";
            return;
        }
        else if (codeS1 == codeS2)
        {
            if (s1I == s1.end() && s2I == s2.end())
            {
                out << "0\n";
                return;
            }
            ++s1I;
            ++s2I;
            ++eqCounter;
            if (s1I == s1.end() && s2I == s2.end())
            {
                out << "0\n";
                return;
            }

            if (s1I != s1.end())
               codeS1 = *s1I;
            if (s1I != s2.end())
               codeS2 = *s2I;

            continue;
        }
        else if (codeS1 > codeS2)
        {
            out << "1\n";
            return;
        }
        else if (codeS1 < codeS2)
        {
            out << "-1\n";
            return;
        }
    }
    out << "0\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        strangeStrCmpTestWrapper();
    else
        strangeStrCmpWrapper(std::cin, std::cout);
    std::cout << "\n";
}
