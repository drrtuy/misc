#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <map>
#include <algorithm>

void groupsWrapper(std::istream& in, std::ostream& out);

void groupsTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    groupsWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;

void groupsTestWrapper()
{
/*
    TestInputType input(8, "");
    input[0] = "8\n";
    input[1] = u8"вышивание крестиком\n";
    MapType map;
    auto res1 = map.insert({input[1], 42});
    std::cout << map[input[1]] << res1.second << "\n";
    auto res2 = map.insert({input[1], 42});
    std::cout << map[input[1]] << res2.second << "\n";
*/
    TestInputType input = { u8"8\n", u8"вышивание крестиком\n", u8"рисование мелками на парте\n", u8"настольный керлинг\n", u8"настольный керлинг\n", u8"кухня африканского племени ужасмай\n", u8"тяжелая атлетика\n", u8"таракановедение\n", u8"таракановедение\n",};
    std::string expected = u8"вышивание крестиком\nрисование мелками на парте\nнастольный керлинг\nкухня африканского племени ужасмай\nтяжелая атлетика\nтаракановедение\n";
    groupsTest(input, expected);
    input.clear();
    expected.clear();
/*
    input = { "123\n", "100003\n", "hash" };
    expected = "6080\n";
    groupsTest(input, expected);
    input.clear();
    expected.clear();

    input = { "123\n", "100003\n", "HaSH" };
    expected = "56156\n";
    groupsTest(input, expected);
    input.clear();
    expected.clear();
*/
}

using DataType = uint64_t;
using MapType = std::map<std::string, DataType>;
void print_map(const MapType& m)
{
    for (const auto& [key, value] : m) {
        std::cout << key << " = " << value << "; ";
    }
    std::cout << "\n";
}


using PairType = std::pair<std::string, DataType>;
using DataVecType = std::vector<PairType>;
void groupsWrapper(std::istream& in, std::ostream& out)
{
    DataType n = 0;
    std::string tmp;
    std::getline(in, tmp);
    std::stringstream iss;
    iss << tmp;
    iss >> n;
    if (!n)
        return;
    tmp.clear();
    MapType map;
    for (size_t i = 0; i < n; ++i)
    {
        std::getline(in, tmp);
        map.insert({tmp, i});
        tmp.clear();
    }
    //print_map(map);

    DataVecType vec(map.begin(), map.end());
    std::sort(vec.begin(), vec.end(),
        [](const PairType& l, const PairType& r)
        {
            return l.second < r.second;
        });
    for (auto& e: vec)
        out << e.first << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        groupsTestWrapper();
    else
        groupsWrapper(std::cin, std::cout);
    std::cout << "\n";
}
