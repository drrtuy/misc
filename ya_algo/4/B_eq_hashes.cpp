#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

void eqHashesWrapper(std::istream& in, std::ostream& out);

void eqHashesTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    eqHashesWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void eqHashesTestWrapper()
{
    TestInputType input = { "123\n", "100003\n", "a" };
    std::string expected = "97\n";
    eqHashesTest(input, expected);
    input.clear();
    expected.clear();

    input = { "123\n", "100003\n", "hash" };
    expected = "6080\n";
    eqHashesTest(input, expected);
    input.clear();
    expected.clear();

    input = { "123\n", "100003\n", "HaSH" };
    expected = "56156\n";
    eqHashesTest(input, expected);
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

using MapType = std::vector<std::string>;

void test(std::ostream& out, MapType& map, const DataType a, const DataType m, const std::string &k)
{
    DataType h = hash(a, m, k);
    if (!map[h].empty())
    {
        if (map[h] != k)
        {
            out << "record " << k << " record " << map[h] << "\n";
            return;
        }
    }
    else
        map[h] = k;
}

void generate(MapType& map, DataType depth, std::string k, std::ostream& out, const DataType a, const DataType m)
{
    if (!depth)
        return test(out, map, a, m, k);

    for (char i = 'a'; i <= 'z'; ++i)
    {
        k.push_back(i);
        generate(map, depth - 1, k, out, a, m);
    }
}

void eqHashesWrapper(std::istream& in, std::ostream& out)
{
    DataType a = 1000ULL, m = 123987123ULL;
    MapType map(123987123, "");

    std::string k = "";
    generate(map, 4, "", out, a, m);
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        eqHashesTestWrapper();
    else
        eqHashesWrapper(std::cin, std::cout);
    std::cout << "\n";
}
