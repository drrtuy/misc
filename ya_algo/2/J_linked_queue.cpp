#include <iostream>
#include <cassert>
#include <sstream>

void linkedQueueWrapper(std::istream& in, std::ostream& out);

void testLinkedQueue()
{
    std::stringstream in;
    in << "10\n";
    in << "put -34\n";
    in << "put -23\n";
    in << "get\n";
    in << "size\n";
    in << "get\n";
    in << "size\n";
    in << "get\n";
    in << "get\n";
    in << "put 80\n";
    in << "size\n";
    std::stringstream ss;
    linkedQueueWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "-34\n1\n-23\n0\nerror\nerror\n1\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "6\n";
    in << "put -66\n";
    in << "put 98\n";
    in << "size\n";
    in << "size\n";
    in << "get\n";
    in << "get\n";
    linkedQueueWrapper(in, ss);
    out = ss.str();
    assert(out == "2\n2\n-66\n98\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "9\n";
    in << "get\n";
    in << "size\n";
    in << "put 74\n";
    in << "get\n";
    in << "size\n";
    in << "put 90\n";
    in << "size\n";
    in << "size\n";
    in << "size\n";
    linkedQueueWrapper(in, ss);
    out = ss.str();
    assert(out == "error\n0\n74\n0\n1\n1\n1\n");
}

using QueueElemType = int32_t;

class QueueNode
{
    public:
        QueueNode(const QueueElemType x) : mValue(x), next(nullptr)
        { }
    QueueElemType get() const
        {
            return mValue;
        } 

        QueueElemType mValue;
        QueueNode* next;
};

class LinkedQueue
{
public:
    LinkedQueue(): mHead(nullptr),
                   mTail(nullptr),
                   mSize(0)
    { }
    void put(const QueueElemType x)
    {
        if (!mSize)
        {
            mHead = new QueueNode(x);
            mTail = mHead;
            ++mSize;
            return;
        }

        ++mSize;
        mTail->next = new QueueNode(x);
        mTail = mTail->next;
    }
    std::string get()
    {
        if (!mSize)
            return "error\n";

        --mSize;
        QueueNode* newHead = mHead->next;
        std::string result = std::to_string(mHead->get()) + "\n";
        delete mHead;
        mHead = newHead;
        if (mSize == 1)
            mTail = mHead;

        return result;
    }
    std::string size()
    {
        return std::to_string(mSize) + "\n";
    }

private:
    QueueNode* mHead;
    QueueNode* mTail;
    size_t mSize;
};

void linkedQueueWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0;
    in >> n;
    LinkedQueue queue;
    for (size_t i = 0; i < n; ++i)
    {
        std::string commandString;
        in >> commandString;
        if (commandString == "put")
        {
            QueueElemType buf = 0;
            in >> buf;
            queue.put(buf);
        }
        else if (commandString == "get")
        {
            out << queue.get();
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
        testLinkedQueue();
    else
        linkedQueueWrapper(std::cin, std::cout);
    std::cout << "\n";
}
