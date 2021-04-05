#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void polyhashWrapper(std::istream& in, std::ostream& out);

void polyhashTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    polyhashWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void polyhashTestWrapper()
{
    TestInputType input = { "123\n", "100003\n", "a" };
    std::string expected = "97\n";
    polyhashTest(input, expected);
    input.clear();
    expected.clear();

    input = { "123\n", "100003\n", "hash" };
    expected = "6080\n";
    polyhashTest(input, expected);
    input.clear();
    expected.clear();

    input = { "123\n", "100003\n", "HaSH" };
    expected = "56156\n";
    polyhashTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = uint64_t;

DataType hash(const DataType a, const DataType m, const std::string& k)
{
    DataType result = static_cast<DataType>(k[0]) * a;
    auto it = k.begin();
    std::advance(it, 1);
    auto last = k.end();
    std::advance(last, -1);
    for (; it != last; ++it)
    {
        result = ((result + static_cast<DataType>(*it)) * a) % m;
    }

    return (result + k.back()) % m;
}

void polyhashWrapper(std::istream& in, std::ostream& out)
{
    DataType a = 0, m = 0;
    in >> a;
    in >> m;
    std::string k;
    in >> k;
    if (k.empty())
    {
        out << "0\n";
        return;
    }
    else if (k.length() == 1)
    {
        out << static_cast<DataType>(k[0]) % m << "\n";
        return;
    }

    out << hash(a, m, k) << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        polyhashTestWrapper();
    else
        polyhashWrapper(std::cin, std::cout);
    std::cout << "\n";
}
