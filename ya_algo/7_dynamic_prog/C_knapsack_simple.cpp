#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>

void knapsackWrapper(std::istream& in, std::ostream& out);

void knapsackTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    knapsackWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void knapsackTestWrapper()
{
    TestInputType input = { "10\n3\n8 1\n2 10\n4 5\n",};
    std::string expected = "36\n";
    knapsackTest(input, expected);
    input.clear();
    expected.clear();

    input = { "10000\n1\n4 20" };
    expected = "80\n";
    knapsackTest(input, expected);
    input.clear();
    expected.clear();
/*
    input = { "7\n11 18\n19 19\n6 15\n14 19\n14 16\n18 21\n22 22\n" };
    expected = "3\n6 15\n19 19\n22 22\n";
    knapsackTest(input, expected);
    input.clear();
    expected.clear();

    input = { "4\n20 21\n20 20\n21 21\n19 20" };
    expected = "4\n19 20\n20 20\n20 21\n21 21\n";
    knapsackTest(input, expected);
    input.clear();
    expected.clear();
*/
}


using DataType = uint64_t;
using Weight = DataType;
using Price = DataType;

struct Pile
{
    Price p;
    Weight w;

    Pile(const Price aP, const Weight aW) : p(aP), w(aW) { }
    bool operator<(const Pile& rhs)
    {
       return p > rhs.p;
    }
};

std::ostream& operator<<(std::ostream& out, const Pile& p)
{
    out << p.p << " " << p.w << std::endl;   
    return out;
} 

using PileVector = std::vector<Pile>;

void knapsackWrapper(std::istream& in, std::ostream& out)
{
    Weight maxWeight;
    in >> maxWeight; 
    DataType n;
    in >> n;
    
    PileVector piles;
    piles.reserve(n);
    Weight w;
    Price p;
    for (size_t i = 0; i < n; ++i)
    {
        in >> p;
        in >> w;
        piles.emplace_back(Pile(p, w));
    }

    if (!maxWeight)
    {
        out << "0" << std::endl;
        return;
    }

    std::sort(piles.begin(), piles.end());
    //for (auto& el: piles)
    //    std::cout << "sorted " << el;

    p = 0; 
    for (auto& pile: piles)
    {
        if (maxWeight < pile.w)
        {
            p += maxWeight * pile.p;
            maxWeight = 0;
            break;
        }
        p += pile.w * pile.p;
        maxWeight -= pile.w;
    }
    out << p << std::endl;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        knapsackTestWrapper();
    else
        knapsackWrapper(std::cin, std::cout);
    std::cout << "\n";
}
