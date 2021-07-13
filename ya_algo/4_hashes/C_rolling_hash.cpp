#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <bits/stdc++.h>

void rollingWrapper(std::istream& in, std::ostream& out);

void rollingTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    rollingWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void rollingTestWrapper()
{
    TestInputType input = { "100\n", "10\n", "a\n", "1\n", "1 1\n",};
    std::string expected = "7\n";
    rollingTest(input, expected);
    input.clear();
    expected.clear();

    input = { "1000\n", "1000009\n", "abcdefgh\n", "7\n", "1 1\n", "1 5\n", "2 3\n", "3 4\n", "4 4\n", "1 8\n", "5 8\n", };
    expected = "97\n225076\n98099\n99100\n100\n436420\n193195\n";
    rollingTest(input, expected);
    input.clear();
    expected.clear();

/*
    input = { "123\n", "100003\n", "hash" };
    expected = "6080\n";
    rollingTest(input, expected);
    input.clear();
    expected.clear();

    input = { "123\n", "100003\n", "HaSH" };
    expected = "56156\n";
    rollingTest(input, expected);
    input.clear();
    expected.clear();
*/
}


using DataType = uint64_t;
const int SIZE = 1000100; 
DataType hashes[SIZE];
DataType pows[SIZE];

DataType hash(const DataType a, const DataType m, const std::string& k)
{
    DataType result = static_cast<DataType>(k[0]) * a;
    auto it = k.begin();
    std::advance(it, 1);
    auto last = k.end();
    std::advance(last, -1);
    for (; it != last; ++it)
    {
        result = ((result + (signed char)*it) * a) % m;
    }

    return (result + k.back()) % m;
}


void initHash(const std::string& target, DataType *h, const DataType a, const DataType mod)
{
    h[0] = 0;
    size_t n = target.length();
    for (size_t i = 1; i <= n; ++i)
    {
        h[i] = (h[i - 1] * a % mod + (signed char)target[i - 1]) % mod;
    }
}

void initPowers(DataType* p, DataType a, DataType mod)
{
    p[0] = 1;
    for (size_t i = 1; i < SIZE; ++i)
        p[i] = p[i - 1] * a % mod;
}

// Make the first pair int
DataType getHash(const DataType l, const DataType r, const DataType *h, const DataType *p, const DataType mod)
{
    return (h[r] + mod - (h[l - 1] * p[r - l + 1]) % mod ) % mod;
}

void rollingWrapper(std::istream& in, std::ostream& out)
{
    DataType a = 0, m = 0;
    size_t n = 0;
    std::string k;
    in >> a >> m >> k >> n;
    if (k.empty())
        return;

    initHash(k, hashes, a, m);
    initPowers(pows, a, m);

    for (size_t i = 0; i < n; ++i)
    {
        DataType l, r;
        in >> l >> r;
        out << getHash(l, r, hashes, pows, m) << "\n"; 
    }

}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        rollingTestWrapper();
    else
        rollingWrapper(std::cin, std::cout);
    std::cout << "\n";
}
