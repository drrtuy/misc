//49670785
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <experimental/random>

#define DEBUG_MACRO(cmd) if (printSteps) cmd

bool printSteps = false;
using DataType = uint64_t;

class Atendee
{
  public:
    Atendee(): mName(""), mP(0), mF(0) {}
    Atendee(const std::string& name, const DataType P, const DataType F): mP(P), mF(F)
    {
        mName = name;
    }
    Atendee& operator=(const Atendee& rhs)
    {
        mName = rhs.mName;
        mP = rhs.mP;
        mF = rhs.mF;
        return *this;
    }
    bool operator>(const Atendee& rhs)
    {
        if (mP > rhs.mP)
            return true;
        if (mP < rhs.mP)
            return false;
        if (mF < rhs.mF)
            return true;
        if (mF > rhs.mF)
            return false;
        return mName < rhs.mName;
    }

    bool operator<(const Atendee& rhs)
    {
        if (mP < rhs.mP)
            return true;
        if (mP > rhs.mP)
            return false;
        if (mF > rhs.mF)
            return true;
        if (mF < rhs.mF)
            return false;
        return mName > rhs.mName;
    }

    std::istream& operator>>(std::istream& in)
    {
        return in;
    }
    const std::string& getName() const
    {
        return mName;
    }
  protected:
    std::string mName;
    DataType mP;
    DataType mF;

  friend std::ostream& operator<<(std::ostream& o, const Atendee&);
  friend std::istream& operator>>(std::istream& o, Atendee&);
};

void quickSWrapper(std::istream& in, std::ostream& out);

void quickSTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    quickSWrapper(in, ss);
    std::string out = ss.str();
    std::cout << "result " << out;
    std::cout << "expected " << expected;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void quickSTestWrapper()
{
    assert(Atendee("alla", 4, 100) < Atendee("gena", 6, 1000));
    assert(Atendee("gosha", 2, 90) > Atendee("rita", 2, 90));
    assert(Atendee("rita", 2, 90) < Atendee("gosha", 2, 90));

    TestInputType input1 = { "2\n", "alla 4 100\n", "gena 6 1000\n" };
    std::string expected1 = "gena\nalla\n";
    quickSTest(input1, expected1);

    TestInputType input2 = { "3\n", "gosha 2 90\n", "rita 2 90\n", "timofey 4 80\n" };
    std::string expected2 = "timofey\ngosha\nrita\n";
    quickSTest(input2, expected2);

    TestInputType input3 = { "3\n", "rita 2 90\n", "gena 6 1000\n", "gosha 2 90\n" };
    std::string expected3 = "gena\ngosha\nrita\n";
    quickSTest(input3, expected3);

    TestInputType input4 = { "5\n", "alla 4 100\n", "gena 6 1000\n", "gosha 2 90\n", "rita 2 90\n", "timofey 4 80\n" };
    std::string expected4 = "gena\ntimofey\nalla\ngosha\nrita\n";
    quickSTest(input4, expected4);
}

// Для отладки
std::ostream& operator<<(std::ostream& out, const Atendee& a)
{
    out << a.mName << " " << a.mP << " " << a.mF;
    return out;
}

std::istream& operator>>(std::istream& in, Atendee& a)
{
    in >> a.mName;
    in >> a.mP;
    in >> a.mF;
    return in;
}

using AtendeeColType = std::vector<Atendee>;
using AtendeeColIter = AtendeeColType::iterator;

void swap(AtendeeColIter left, AtendeeColIter right)
{
    DEBUG_MACRO(std::cout << "swaping " << *left << " and " << *right << "\n");
    // Можно было бы move operator= сделать, но ограничения по таймингам пропускают и copy.
    Atendee tmp = *left;
    *left = *right;
    *right = tmp;
}

std::pair<AtendeeColIter, AtendeeColIter> partition(AtendeeColType& atendees,
                                                    AtendeeColIter left,
                                                    AtendeeColIter right,
                                                    const Atendee pivot)
{
    AtendeeColIter leftSwap = atendees.end(), rightSwap = atendees.end();
    DEBUG_MACRO(std::cout << "pivot " << pivot << "\n");
    DEBUG_MACRO(std::cout << "before partition ");
    DEBUG_MACRO(for(auto &e: atendees) std::cout << e << " ");
    DEBUG_MACRO(std::cout << "\n");
    DEBUG_MACRO(std::cout << "left " << *left << "\n");
    DEBUG_MACRO(std::cout << "right " << *right << "\n");

    while (right - left >= 1)
    {
        if (leftSwap == atendees.end() && *left > pivot)
            left++;
        else
            leftSwap = left;
        if (rightSwap == atendees.end() && *right < pivot)
            right--;
        else
            rightSwap = right;
       
        if (leftSwap != atendees.end() && rightSwap != atendees.end())
        {
            swap(left, right);
            ++left;
            --right;
            rightSwap = atendees.end();
            leftSwap = atendees.end();
        }
    }
    DEBUG_MACRO(std::cout << "after partition ");
    DEBUG_MACRO(for(auto &e: atendees) std::cout << e << " ");
    DEBUG_MACRO(std::cout << "\n");
    // Меняем местами 
    return std::make_pair(right, left);
}

void quickS(AtendeeColType& atendees, AtendeeColIter left, AtendeeColIter right)
{
    int originalSize = right - left;
    if (originalSize <= 1)
    {
        DEBUG_MACRO(std::cout << "base case " << *left << " " << *right << "\n");
        if (*left < *right)
            swap(left, right);
        return;
    }

    size_t offset = left - atendees.begin();
    const Atendee& pivot = atendees[offset + std::experimental::randint(0, originalSize - 1)];
    // Пара: first - left, second - right
    auto leftRight = partition(atendees, left, right, pivot);

    quickS(atendees, left, leftRight.first);
    quickS(atendees, leftRight.second, right);
} 

void quickSWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0;
    in >> n;
    
    Atendee tmp;
    AtendeeColType atendees;
    atendees.reserve(n);
    for(size_t i = 0; i < n; ++i)
    {
        in >> tmp;
        // Здесь также можно заиспользовать move semantics.
        atendees.push_back(tmp);
    }

    quickS(atendees, atendees.begin(), atendees.end() - 1);

    for(auto &e: atendees)
        out << e.getName() << "\n";
    
    return;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
    {
        printSteps = true;
        quickSTestWrapper();
    }
    else
        quickSWrapper(std::cin, std::cout);
    std::cout << "\n";
}
