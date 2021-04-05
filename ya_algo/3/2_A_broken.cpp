//49669268
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <numeric>
#include <iterator>
#include <algorithm>

#define DEBUG_MACRO(cmd) if (printSteps) cmd
bool printSteps = false;

void brokenArrayWrapper(std::istream& in, std::ostream& out);

void brokenArrayTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    brokenArrayWrapper(in, ss);
    std::string out = ss.str();
    std::cout << "result " << out;
    std::cout << "expected " << expected;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void brokenArrayTestWrapper()
{
    TestInputType input1 = { "9\n", "5\n", "19 21 100 101 1 4 5 7 12\n", };
    std::string expected1 = "6\n";
    brokenArrayTest(input1, expected1);

    TestInputType input2 = { "9\n", "50\n", "19 21 100 101 1 4 5 7 12\n", };
    std::string expected2 = "-1\n";
    brokenArrayTest(input2, expected2);

    TestInputType input3 = { "9\n", "5\n", "1 4 5 7 12 19 21 100 101\n", };
    std::string expected3 = "2\n";
    brokenArrayTest(input3, expected3);

    TestInputType input4 = { "2\n", "5\n", "5 1\n", };
    std::string expected4 = "0\n";
    brokenArrayTest(input4, expected4);

    size_t size = 10;
    for (size_t i = 0; i < size; ++i)
    {
        std::vector<uint64_t> numbers(size);
        std::iota(numbers.begin(), numbers.end() - i , i + 1);
        if (i)
            std::iota(numbers.end() - i, numbers.end(), 1);
        std::ostringstream oss;
        std::copy(numbers.begin(), numbers.end()-1, std::ostream_iterator<int>(oss, " "));
        oss << numbers.back();
        DEBUG_MACRO(std::cout << oss.str() << "\n");
        for (size_t it = 1; it <= size; ++it)
        {
            TestInputType input;
            input.push_back(std::to_string(size) + "\n");
            input.push_back(std::to_string(it) + "\n");
            input.push_back(oss.str() + "\n");
            auto targetIter = std::find(numbers.begin(), numbers.end(), it);
            std::string expected(std::to_string(std::distance(numbers.begin(), targetIter)) + "\n");
            brokenArrayTest(input, expected);
        }
    }
}

// Для поиска элемента используется модифицированный рекурсивный бинарный поиск.
// Алгоритм поиска: заданая последовательность делится на две почти равные
// части, в одной из которых последовательность терпит разрыв, т.е. элемент
// в начале > элемента конца. Если это так, то проверяем входит ли искомый
// элемент в ту часть, что полностью отсортирована. Если входит, то рекурсивно
// запускаем бинарный поиск на этой половине, в противном случае запускаем
// поиск на части с разрывом. Есть несколько базовых случаев бинарного поиска: по
// одному элементу, по двум, если в паре присутствует разрыв, если искомый
// элемент в середине.
// Изложенный алгоритм доказывает конечность и верность алгоритма.
// Алгоритм не требует доп. памяти.
// Сложность алгоритма по кол-ву операций log(N), т.к. на каждом шаге кол-во
// рассматриваемых элементов уменьшается вдвое.

using DataType = uint64_t;
using BrokenArrayType = std::vector<DataType>;
using IterType = BrokenArrayType::const_iterator;

class BrokenArray
{
  public:
    BrokenArray(std::istream& in, const DataType n)
    {
        brokenArray.reserve(n);
        DataType tmp;
        for (size_t i = 0; i < n; ++i)
        {
            in >> tmp;
            brokenArray.push_back(tmp);
        }
    }

    std::string binarySearch(const DataType k) const
    {
        IterType first = brokenArray.begin(), last = brokenArray.end() - 1;
        DEBUG_MACRO(std::cout << "binarySearch target " << k << "\n");
        return std::to_string(_binarySearch(first, last, k));
    }

    int64_t _binarySearch(IterType& first,
                          IterType& last,                  
                          const DataType k) const;

    inline int64_t _distance1Case(IterType& first,
                           IterType& second,
                           const DataType k) const;
    
    inline int64_t _binarySearchMidRight(IterType& first, 
                                         IterType& last,    
                                         const DataType k) const;
  private:
    BrokenArrayType brokenArray;
    DataType k;
};

inline int64_t BrokenArray::_binarySearchMidRight(IterType& first, 
                                                  IterType& last,    
                                                  const DataType k) const
{
    std::advance(first, 1);
    return _binarySearch(first, last, k);
}

int64_t BrokenArray::_distance1Case(IterType& first,
                       IterType& second,
                       const DataType k) const
{
    if (k == *first)
        return first - brokenArray.begin();
    if (k == *second)
        return second - brokenArray.begin();
    return -1;
}

int64_t BrokenArray::_binarySearch(IterType& first,
                                   IterType& last,                  
                                   const DataType k) const
{
    DEBUG_MACRO(std::cout << "binarySearch first " << *first << " last " << *last << "\n");
    if (first == last)
    {
        return k == *first ? first - brokenArray.begin() : -1;
    }
    size_t distance = std::distance(first, last);

    DEBUG_MACRO(std::cout << "binarySearch distance " << distance << "\n");
    IterType middle = first;
    std::advance(middle, distance / 2);

    bool leftRunIsBroken = *first > *middle;
    bool rightRunIsBroken = *middle > *last;

    if (leftRunIsBroken)
    {
        DEBUG_MACRO(std::cout << "binarySearch leftBroken " << distance << "\n");
       
        // Если между двумя элементами разрыв. 
        if (distance == 1)
            return _distance1Case(first, last, k);

        return k > *middle && k <= *last
            ? _binarySearchMidRight(middle, last, k)
            : _binarySearch(first, middle, k);
    }
    else if (rightRunIsBroken)
    {
        DEBUG_MACRO(std::cout << "binarySearch rightBroken " << distance << "\n");
        // Если между двумя элементами разрыв. 
        if (distance == 1)
            return _distance1Case(first, last, k);

        return k >= *first && k <= *middle
            ? _binarySearch(first, middle, k)
            : _binarySearchMidRight(middle, last, k);
    }

    // Обе подпоследовательности сортированы.
    if (k < *middle)
        return _binarySearch(first, middle, k);
    else if (k > *middle)
        return _binarySearchMidRight(middle, last, k);

    // k найден досрочно в middle.
    DEBUG_MACRO(std::cout << "baseCase returns " << middle - brokenArray.begin() << "\n");
    return middle - brokenArray.begin();
} 

void brokenArrayWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0;
    in >> n;
    DataType k = 0, tmp = 0;
    in >> k;
      
    if (n == 0)
    {
        out << "-1\n";
        return;
    }

    if (n == 1)
    {
        in >> tmp;
        k == tmp ? out << "0\n" : out << "-1\n";
        return;
    }
 
    BrokenArray brokenArray(in, n);
    out << brokenArray.binarySearch(k) << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
//    put any argument to follow unit testing path
    if (argc > 1)
    {
        printSteps = true;
        brokenArrayTestWrapper();
    }
    else
        brokenArrayWrapper(std::cin, std::cout);
    std::cout << "\n";
}
