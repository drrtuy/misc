// Contest test run ID 48228488
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <unordered_map>

void phoneNumbWrapper(std::istream& in, std::ostream& out);

void testPhoneNumb()
{
    std::stringstream in;
    in << "23\n";
    std::stringstream ss;
    phoneNumbWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "ad ae af bd be bf cd ce cf \n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "92\n";
    phoneNumbWrapper(in, ss);
    out = ss.str();
    assert(out == "wa wb wc xa xb xc ya yb yc za zb zc \n");
}

using ResultOutputType = std::string;
using IterType = std::string::const_iterator;
using DictType = std::vector<std::vector<std::string>>;
const DictType digitsToCharsDict = {{""}, 
                                    {"a", "b", "c"},
                                    {"d", "e", "f"},
                                    {"g", "h", "i"},
                                    {"j", "k", "l"},
                                    {"m", "n", "o"},
                                    {"p", "q", "r", "s"},
                                    {"t", "u", "v"},
                                    {"w", "x", "y", "z"},
};

void phoneNumbRecursion(IterType digitsStringBegin, IterType digitsStringEnd, std::string charsString, std::ostream& out)
{
    if (digitsStringBegin == digitsStringEnd)
    {
        out << charsString << " ";
        return;
    }
   
    char nextDigit = *digitsStringBegin - '1';
    for (auto charSymbol: digitsToCharsDict[nextDigit])
    {
        phoneNumbRecursion(digitsStringBegin + 1, digitsStringEnd, charsString + charSymbol, out);
    }
}

void phoneNumbWrapper(std::istream& in, std::ostream& out)
{
    std::string digitsString;
    in >> digitsString;
    if (digitsString.empty())
        return;
    phoneNumbRecursion(digitsString.begin(), digitsString.end(), "", out);
    out << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testPhoneNumb();
    else
        phoneNumbWrapper(std::cin, std::cout);
    std::cout << "\n";
}
