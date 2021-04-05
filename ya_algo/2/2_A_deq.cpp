// 48922541
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <functional>

void limitedDeqWrapper(std::istream& in, std::ostream& out);

void testLimitedDeq()
{
    std::stringstream in;
    in << "4\n";
    in << "4\n";
    in << "push_front 861\n";
    in << "push_front -819\n";
    in << "pop_back\n";
    in << "pop_back\n";
    std::stringstream ss;
    limitedDeqWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "861\n-819\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
	in << "7\n";
	in << "10\n";
	in << "push_front -855\n";
	in << "push_front 720\n";
	in << "pop_back\n";
	in << "pop_back\n";
	in << "push_back 844\n";
	in << "pop_back\n";
	in << "push_back 823\n";
    limitedDeqWrapper(in, ss);
    out = ss.str();
    assert(out == "-855\n720\n844\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
	in << "6\n";
	in << "6\n";
	in << "push_front -201\n";
	in << "push_back 959\n";
	in << "push_back 102\n";
	in << "push_front 20\n";
	in << "pop_front\n";
	in << "pop_back\n";
	limitedDeqWrapper(in, ss);
    out = ss.str();
    assert(out == "20\n102\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "8\n";
    in << "4\n";
    in << "push_back 861\n";
    in << "push_back -819\n";
    in << "push_back -820\n";
    in << "pop_front\n";
    in << "pop_front\n";
    in << "push_front -821\n";
    in << "push_front -822\n";
    in << "pop_back\n";
    limitedDeqWrapper(in, ss);
    out = ss.str();
    assert(out == "861\n-819\n-820\n");
}

using QueueElemType = int32_t;
using IdxElemType = size_t;
const std::string errMsg("error\n");
const std::string emptyMsg("");

/*
    deq реализован на базе вектора с двухсторонним движением индексов head и tail.
    Добавил абстракции и задействовал шаблоны, для уменьшения boilerplate, что
    сделало код менее читаемым, но более изящным.
    Предыдущая версия кода без шаблонов была доступна в запуске 48809608.

    Временная сложность операций O(1).
    Пространственная сложность O(1).
*/
class LimitedDeq
{
public:
    LimitedDeq(const uint16_t size = 1000,
               const bool debug = false): mHead(0),
                                          mTail(0),
                                          mSize(0),
                                          mDebug(debug)
    {
        // Верно. Совсем забыл про эту часть. Странно почему не взорвалось
        // operator[].
        mQueueVector.resize(size, 0);
    }

    template<class F, class S>
    std::string push(const QueueElemType x,
                     IdxElemType& firstCheckAsignmentMember,
                     const IdxElemType firstCheckCompareLimit,
                     const IdxElemType firstCheckTrueValue,
                     IdxElemType& secondCheckAsignmentMember,
                     const IdxElemType secondCheckCompareLimit,
                     const IdxElemType secondCheckTrueValue)
    {
        // Нет места - выходим.
        if (mSize == mQueueVector.capacity())
            return errMsg;

        // Добавляем элемент в вектор.
        mQueueVector[secondCheckAsignmentMember] = x;
        ++mSize;

        if (mDebug)
            std::cout << "!!!! begin push: Head " << mHead << " Tail " << mTail << "\n";

        // При пустом deq head = tail - разносим head и tail, после вставки первого элемента.
        if (mSize == 1)
        {
            F op = F();
            IdxElemType firstCheckNextValue = op(firstCheckAsignmentMember, 1);
            // Проверка на wraparound
            firstCheckAsignmentMember = (firstCheckNextValue == firstCheckCompareLimit) ? firstCheckTrueValue
                                                                                        : firstCheckNextValue;
        }

        S op = S();
        IdxElemType secondCheckNextValue = op(secondCheckAsignmentMember, 1);
        // Проверка на wraparound
        secondCheckAsignmentMember = (secondCheckNextValue == secondCheckCompareLimit) ? secondCheckTrueValue  
                                                                                       : secondCheckNextValue;
        if (mDebug)
            std::cout << "!!!! end push: Head " << mHead << " Tail " << mTail << "\n";
        return emptyMsg;
    }

    std::string push_back(const QueueElemType x)
    {
        return push<std::plus<IdxElemType>, std::minus<IdxElemType>>(x,
                                                                     mHead,
                                                                     mQueueVector.capacity(),
                                                                     0ULL,
                                                                     mTail,
                                                                     std::numeric_limits<IdxElemType>::max(),
                                                                     mQueueVector.capacity() - 1);
    }

    std::string push_front(const QueueElemType x)
    {
        return push<std::minus<IdxElemType>, std::plus<IdxElemType>>(x,
                                                                     mTail,
                                                                     std::numeric_limits<decltype(mTail)>::max(),
                                                                     mQueueVector.capacity() - 1,
                                                                     mHead,
                                                                     mQueueVector.capacity(),
                                                                     0);
    }

    template<class O>
    std::string pop(IdxElemType& idxRef,
                    const IdxElemType idxCompareLimit,
                    const IdxElemType idxCompareTrueValue,
                    IdxElemType& secondaryIdxRef)
    {
        // deq пустой - выходим.
        if (!mSize)
            return errMsg;
    
        if (mDebug)
            std::cout << "!!!! begin pop_front: Head " << mHead << " Tail " << mTail << "\n";

        // Уменьшаем размер deq-а
        mSize = (mSize < 2) ? 0 : --mSize;
        
        O op = O();
        IdxElemType idxNextValue = op(idxRef, 1);
        // Проверка на wraparound
        idxRef = (idxNextValue == idxCompareLimit) ? idxCompareTrueValue
                                                   : idxNextValue;

        // deq пустой, поэтому Head = Tail
        if (!mSize)
            secondaryIdxRef = idxRef;
        if (mDebug)
            std::cout << "!!!! end pop_front: Head " << mHead << " Tail " << mTail << "\n";
        return std::to_string(mQueueVector[idxRef]) + "\n";
    }

    std::string pop_front()
    {
        return pop<std::minus<QueueElemType>>(mHead,
                                              std::numeric_limits<IdxElemType>::max(),
                                              mQueueVector.capacity() - 1,
                                              mTail);
    }

    std::string pop_back()
    {
        return pop<std::plus<QueueElemType>>(mTail, mQueueVector.capacity(), 0ULL, mHead);
    }

private:
    std::vector<QueueElemType> mQueueVector;
    size_t mHead;
    size_t mTail;
    size_t mSize;
    bool mDebug;
};

void limitedDeqWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0, maxSize = 0;
    in >> n;
    in >> maxSize;
    LimitedDeq queue(maxSize);
    // Не очень красивая реализация, но не хотелось усложнять введением Fabric
    // или диспетчера на базе map.
    // Сравниваем полученную команду и дёргаем соответствующий метод класса.
    for (size_t i = 0; i < n; ++i)
    {
        std::string commandString;
        in >> commandString;
        if (commandString == std::string("push_front") ||
            commandString == std::string("push_back"))
        {
            QueueElemType buf = 0;
            in >> buf;
            if (commandString == std::string("push_front"))
                out << queue.push_front(buf);

            if (commandString == std::string("push_back"))
                out << queue.push_back(buf);
        }
        else if (commandString == std::string("pop_front"))
        {
            out << queue.pop_front();

        }
        else if (commandString == std::string("pop_back"))
            out << queue.pop_back();
    }
}

int main(int argc, char** argv)
{
    //std::ios_base::sync_with_stdio(false);
    //std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testLimitedDeq();
    else
        limitedDeqWrapper(std::cin, std::cout);
    std::cout << "\n";
}
