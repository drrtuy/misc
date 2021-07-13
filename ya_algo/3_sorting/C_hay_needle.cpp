#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <unordered_map>

void stackNeedleWrapper(std::istream& in, std::ostream& out);

void testStackNeedle()
{
    std::stringstream in;
    in << "abc\n";
    in << "ahbgdcu\n";
    std::stringstream ss;
    stackNeedleWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "True\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "\n";
    in << "ahbgdcu\n";
    stackNeedleWrapper(in, ss);
    out = ss.str();
    assert(out == "True\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "abc\n";
    in << "\n";
    stackNeedleWrapper(in, ss);
    out = ss.str();
    assert(out == "False\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "abcp\n";
    in << "ahpc\n";
    stackNeedleWrapper(in, ss);
    out = ss.str();
    assert(out == "False\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "abcp\n";
    in << "ah\n";
    stackNeedleWrapper(in, ss);
    out = ss.str();
    assert(out == "False\n");
}

std::string stackNeedle(std::string& s, std::string& n)
{
    std::string::const_iterator stackPos = s.begin();
    std::string::const_iterator needlePos = n.begin();
    while (stackPos != s.end() && needlePos != n.end())
    {
        if (*stackPos++ == *needlePos)
            ++needlePos;
    }
    return (needlePos == n.end()) ? "True" : "False";
}

void stackNeedleWrapper(std::istream& in, std::ostream& out)
{
    std::string n;
    std::string s;
    std::getline(in, n);
    std::getline(in, s);
    if (n.empty())
    {
        out << "True\n";
        return;
    }
    if (s.empty() && !n.empty())
    {
        out << "False\n";
        return;
    }

    out << stackNeedle(s, n) << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testStackNeedle();
    else
        stackNeedleWrapper(std::cin, std::cout);
    std::cout << "\n";
}
