#include <iostream>
#include <cassert>
#include <sstream>
#include <stack>

void parenthesisCheckerWrapper(std::istream& in, std::ostream& out);

void testParenthesisChecker()
{
    std::stringstream in;
    in << "{[()]}\n";
    std::stringstream ss;
    parenthesisCheckerWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "True\n");
    
    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "\n";
    parenthesisCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "True\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "()[]{}\n";
    parenthesisCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "True\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "()[{}{}]\n";
    parenthesisCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "True\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "([){}{}]\n";
    parenthesisCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "False\n");
}

using parenthesisCheckerStack = std::stack<char>;

bool isPair(const char x, const char y)
{
    return ((y == ']' && x == '[') ||
           (y == '}' && x == '{') ||
           (y == ')' && x == '('));
}

bool parenthesisCheck(std::string& inputString)
{
    parenthesisCheckerStack stack;
    for (char ch: inputString)
    {
        if (ch == '[' || ch == '{' || ch == '(')
            stack.push(ch);
        else if (ch == ']' || ch == '}' || ch == ')')
        {
            if (stack.empty() || !(isPair(stack.top(), ch)))
                return false;
            stack.pop();
        }
    }
    return stack.empty();
}

void parenthesisCheckerWrapper(std::istream& in, std::ostream& out)
{
    std::string inputString;
    in >> inputString;
    if (inputString.back() == '\n')
        inputString.pop_back();
    if (parenthesisCheck(inputString))
        out << "True" << "\n";
    else
        out << "False" << "\n";
}

int main(int argc, char** argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testParenthesisChecker();
    else
        parenthesisCheckerWrapper(std::cin, std::cout);
    std::cout << "\n";
}
