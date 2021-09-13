#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void reversedLineWrapper(std::istream& in, std::ostream& out);

void reversedLineTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    reversedLineWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void reversedLineTestWrapper()
{
    TestInputType input = { "one two three\n",};
    std::string expected = "three two one \n";
    reversedLineTest(input, expected);
    input.clear();
    expected.clear();

    input = { "hello\n" };
    expected = "hello \n";
    reversedLineTest(input, expected);
    input.clear();
    expected.clear();

    input = { "may the force be with you\n" };
    expected = "you with be force the may \n";
    reversedLineTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = uint64_t;
using Line = std::vector<std::string>;

void reversedLineWrapper(std::istream& in, std::ostream& out)
{
    std::string tmp;
    Line line;
    line.reserve(1000);
    size_t l = 0;
    do
    {
        in >> tmp;
        l = tmp.length();
        if (l)
            line.push_back(std::move(tmp));
    } while (l);
    for (auto wI = line.end() - 1; wI >= line.begin(); -- wI)
        out << *wI << " ";
    out << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        reversedLineTestWrapper();
    else
        reversedLineWrapper(std::cin, std::cout);
    std::cout << "\n";
}
