// Contest test run ID 48228488
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

void maxStackWrapper(std::istream& in, std::ostream& out);

void testMaxStack()
{
    std::stringstream in;
    in << "8\n";
    in << "get_max\n";
    in << "push 7\n";
    in << "pop\n";
    in << "push -2\n";
    in << "push -1\n";
    in << "pop\n";
    in << "get_max\n";
    in << "get_max\n";
    std::stringstream ss;
    maxStackWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "None\n-2\n-2\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "7\n";
    in << "get_max\n";
    in << "pop\n";
    in << "pop\n";
    in << "pop\n";
    in << "push 10\n";
    in << "get_max\n";
    in << "push -9\n";
    maxStackWrapper(in, ss);
    out = ss.str();
    assert(out == "None\nerror\nerror\nerror\n10\n");
}

using StackElemType = int32_t;

class MaxStack
{
public:
    MaxStack(const uint16_t size = 1000)
    {
        stackVector.reserve(size);
        trackVector.reserve(size);
    }
    void push(const StackElemType x)
    {
        if (stackVector.empty())
        {
            trackVector.push_back(x);
        }
        else
        {
            StackElemType buf = (trackVector.back() > x) ? trackVector.back() : x;
            trackVector.push_back(buf);
        }
        stackVector.push_back(x);
    }
    std::string pop()
    {
        if (stackVector.empty())
            return "error\n";
    
        stackVector.pop_back();
        trackVector.pop_back();

        return "";
    }
    std::string get_max()
    {
        if (stackVector.empty())
            return "None\n";

        StackElemType buf = trackVector.back();
        return std::to_string(buf) + "\n";
    }

private:
    std::vector<StackElemType> stackVector;
    std::vector<StackElemType> trackVector;
};

void maxStackWrapper(std::istream& in, std::ostream& out)
{
    MaxStack stack;
    size_t n = 0;
    in >> n;
    for (size_t i = 0; i < n; ++i)
    {
        std::string commandString;
        in >> commandString;
        if (commandString == "push")
        {
            StackElemType buf = 0;
            in >> buf;
            stack.push(buf);
        }
        else if (commandString == "pop")
        {
            out << stack.pop();
        }
        else if (commandString == "get_max")
        {
            out << stack.get_max();
        }
    }
}

int main(int argc, char** argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testMaxStack();
    else
        maxStackWrapper(std::cin, std::cout);
    std::cout << "\n";
}
