#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

void limitedQueueWrapper(std::istream& in, std::ostream& out);

void testLimitedQueue()
{
    std::stringstream in;
    in << "8\n";
    in << "2\n";
    in << "peek\n";
    in << "push 5\n";
    in << "push 2\n";
    in << "peek\n";
    in << "size\n";
    in << "size\n";
    in << "push 1\n";
    in << "size\n";
    std::stringstream ss;
    limitedQueueWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "None\n5\n2\n2\nerror\n2\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "10\n";
    in << "1\n";
    in << "push 1\n";
    in << "size\n";
    in << "push 3\n";
    in << "size\n";
    in << "push 1\n";
    in << "pop\n";
    in << "push 1\n";
    in << "pop\n";
    in << "push 3\n";
    in << "push 3\n";
    limitedQueueWrapper(in, ss);
    std::cout << out;
    assert(out == "1\nerror\n1\nerror\n1\n1\nerror\n");
}

using QueueElemType = int32_t;

class LimitedQueue
{
public:
    LimitedQueue(const uint16_t size = 5000): mHead(0),
                                              mTail(0),
                                              mMaxSize(size),
                                              mSize(0)
    {
        mQueueVector.reserve(size);
    }
    std::string push(const QueueElemType x)
    {
        if (mSize == mMaxSize)
            return "error\n";

        mQueueVector[mTail] = x;
        mTail = ( mTail + 1 ) % mMaxSize;
        mSize += 1;
        return "";
    }
    std::string pop()
    {
        if (!mSize)
            return "None\n";
        mSize -= 1;
        std::string result = std::to_string(mQueueVector[mHead]) + "\n";
        mHead = (mHead + 1) % mMaxSize;
        return result;
    }
    std::string peek()
    {
        if (!mSize)
            return "None\n";
        return std::to_string(mQueueVector[mHead]) + "\n";
    }
    std::string size()
    {
        return std::to_string(mSize) + "\n";
    }

private:
    std::vector<QueueElemType> mQueueVector;
    size_t mHead;
    size_t mTail;
    size_t mMaxSize;
    size_t mSize;
};

void limitedQueueWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0, maxSize = 0;
    in >> n;
    in >> maxSize;
    LimitedQueue queue(maxSize);
    for (size_t i = 0; i < n; ++i)
    {
        std::string commandString;
        in >> commandString;
        if (commandString == "push")
        {
            QueueElemType buf = 0;
            in >> buf;
            out << queue.push(buf);
        }
        else if (commandString == "pop")
        {
            out << queue.pop();
        }
        else if (commandString == "peek")
        {
            out << queue.peek();
        }
        else if (commandString == "size")
        {
            out << queue.size();
        }
    }
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testLimitedQueue();
    else
        limitedQueueWrapper(std::cin, std::cout);
    std::cout << "\n";
}
