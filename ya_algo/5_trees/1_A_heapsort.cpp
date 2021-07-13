// 52081330 
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <experimental/random>

#define DEBUG_MACRO(cmd) if (printSteps) cmd

// Применяется тривиальный алгоритм heap sort: 
// 1 Собираем кучу: в конец массива размера N + 1 добавляем новый элемент и запускаем SiftUp. В конце имеем кучу упорядоченную по возрастанию.
// 2 В цикле снимаем верхушку кучи, ставим хвост кучи в начало и запускаем siftDown. Из-за инварианта кучи в результате имеем сортированную по неубыванию последовательность.
// Сложность по CPU N*logN, по памяти N.

bool printSteps = false;
using DataType = uint64_t;
using IdxType = size_t;

class Atendee
{
  public:
    Atendee(): mName(""), mP(0), mF(0) {}
    Atendee(const std::string& name, const DataType P, const DataType F): mP(P), mF(F)
    {
        mName = name;
    }
    Atendee(Atendee&& a)
    {
        mName.assign(std::move(a.mName));
        mP = a.mP;
        mF = a.mF;
    }
    Atendee(const Atendee& a) : mName(a.mName), mP(a.mP), mF(a.mF) {};
    Atendee(std::istream& in)
    {
        in >> mName;
        in >> mP;
        in >> mF;
    }
    ~Atendee()
    {
        mName.clear();
    }
    Atendee& operator=(Atendee&& rhs)
    {
        mName.assign(rhs.mName);
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
    std::string mName;
    DataType mP;
    DataType mF;

  friend std::ostream& operator<<(std::ostream& o, const Atendee&);
};

class Heap
{
  public:
    Heap(const size_t size)
    {
        mHeap.reserve(size + 1);
        mHeap.emplace_back(Atendee());
    }
    void emplaceBack(Atendee&& a)
    {
        mHeap.emplace_back(a);
        siftUp(mHeap.size() - 1);    
    }
    bool empty() const { return mHeap.size() == 1; }
    Atendee popTop()
    {
        Atendee ret(std::move(mHeap[1]));
        mHeap[1] = std::move(mHeap.back());
        mHeap.pop_back();
        siftDown(1);
        return ret;
    }
 
    void siftDown(IdxType idx)
    {
        IdxType left = 2 * idx;
        IdxType right = left + 1;

        IdxType maxIdx = right < mHeap.size() && mHeap[left] < mHeap[right] ? right : left;
        while (left < mHeap.size() && mHeap[idx] < mHeap[maxIdx])
        {
            Atendee buf(std::move(mHeap[maxIdx]));
            mHeap[maxIdx] = std::move(mHeap[idx]);
            mHeap[idx] = std::move(buf);

            idx = maxIdx;
            left = 2 * idx;
            right = left + 1;
            maxIdx = right < mHeap.size() && mHeap[left] < mHeap[right] ? right : left;
        }
    }

    void siftUp(IdxType idx)
    {
        if (idx == 1)
            return;
        IdxType parent = idx / 2;

        while (idx > 1 && mHeap[idx] > mHeap[parent])
        {
            Atendee buf(std::move(mHeap[parent]));
            mHeap[parent] = std::move(mHeap[idx]);
            mHeap[idx] = std::move(buf);

            idx = parent;
            parent = idx / 2;
        }
    }

    std::vector<Atendee> mHeap;
};

void heapSWrapper(std::istream& in, std::ostream& out);

void heapSTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    heapSWrapper(in, ss);
    std::string out = ss.str();
    std::cout << "result " << out;
    std::cout << "expected " << expected;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void heapSTestWrapper()
{
    assert(Atendee("alla", 4, 100) < Atendee("gena", 6, 1000));
    assert(Atendee("gosha", 2, 90) > Atendee("rita", 2, 90));
    assert(Atendee("rita", 2, 90) < Atendee("gosha", 2, 90));

    TestInputType input1 = { "2\n", "alla 4 100\n", "gena 6 1000\n" };
    std::string expected1 = "gena\nalla\n";
    heapSTest(input1, expected1);

    TestInputType input2 = { "3\n", "gosha 2 90\n", "rita 2 90\n", "timofey 4 80\n" };
    std::string expected2 = "timofey\ngosha\nrita\n";
    heapSTest(input2, expected2);

    TestInputType input3 = { "3\n", "rita 2 90\n", "gena 6 1000\n", "gosha 2 90\n" };
    std::string expected3 = "gena\ngosha\nrita\n";
    heapSTest(input3, expected3);

    TestInputType input4 = { "5\n", "alla 4 100\n", "gena 6 1000\n", "gosha 2 90\n", "rita 2 90\n", "timofey 4 80\n" };
    std::string expected4 = "gena\ntimofey\nalla\ngosha\nrita\n";
    heapSTest(input4, expected4);
}

std::ostream& operator<<(std::ostream& out, const Atendee& a)
{
    out << a.mName;
    return out;
}

using AtendeeColType = std::vector<Atendee>;
using AtendeeColIter = AtendeeColType::iterator;

void heapSWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0;
    in >> n;
    
    Heap atendees(n);
    for(size_t i = 0; i < n; ++i)
        atendees.emplaceBack(Atendee(in));

    while(!atendees.empty())
        out << atendees.popTop() << "\n";
    
    return;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
    {
        printSteps = false;
        heapSTestWrapper();
    }
    else
        heapSWrapper(std::cin, std::cout);
    std::cout << "\n";
}
