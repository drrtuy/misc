#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

void substrWrapper(std::istream& in, std::ostream& out);

void substrTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    substrWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void substrTestWrapper()
{
    TestInputType input = { "abcabcbb" };
    std::string expected = "3\n";
    substrTest(input, expected);
    input.clear();
    expected.clear();

    input = { "bbbbbb\n" };
    expected = "1\n";
    substrTest(input, expected);
    input.clear();
    expected.clear();

    input = { "abcdebbac\n" };
    expected = "5\n";
    substrTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = uint64_t;
using DictType = std::vector<DataType>;
void substrWrapper(std::istream& in, std::ostream& out)
{
    DataType emptyMagic = std::numeric_limits<DataType>::max();
    DictType dict(256, emptyMagic);
    std::string line;
    in >> line;
    if (line.empty())
    {
        return;
    }
    else if (line.length() == 1)
    {
        out << 1 << "\n";
        return;
    }
    size_t maxLength = 0;
    size_t length = 0;

    for (auto it = line.begin(); it != line.end(); ++it)
    {
        if (dict[*it] == emptyMagic)
        {
            dict[*it] = it - line.begin();
            ++length;
            //std::cout << "empty dict slot for " << *it << " dict[*it] " << dict[*it]  << " length " << length << "\n";
        }
        else if (it - line.begin() - length <= dict[*it])
        {
            length = it - line.begin() - dict[*it];
            dict[*it] = it - line.begin();
            //std::cout << "reducing length for " << *it << " dict[*it] " << dict[*it]  << " length " << length << "\n";
        }
        else if (it - line.begin() - length > dict[*it])
        {
            dict[*it] = it - line.begin();
            ++length;
            //std::cout << "raising length for " << *it << " dict[*it] " << dict[*it]  << " length " << length << "\n";
        }
        maxLength = std::max(maxLength, length);
    }  
    out << maxLength << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        substrTestWrapper();
    else
        substrWrapper(std::cin, std::cout);
    std::cout << "\n";
}
