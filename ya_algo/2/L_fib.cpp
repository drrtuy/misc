#include <iostream>
#include <cassert>
#include <sstream>
#include <stack>

void fibCheckerWrapper(std::istream& in, std::ostream& out);

void testParenthesisChecker()
{
    std::stringstream in;
    in << "3 1\n";
    std::stringstream ss;
    fibCheckerWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "3\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "39 9\n";
    fibCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "102334155\n");
}

using fibDataType = uint64_t;

fibDataType powerOfTen[] = {
    1ULL,
    10ULL,
    100ULL,
    1000ULL,
    10000ULL,
    100000ULL,
    1000000ULL,
    10000000ULL,
    100000000ULL,
    1000000000ULL,
};

void fibCheckerWrapper(std::istream& in, std::ostream& out)
{
    fibDataType n = 0, sum = 0, f0 = 1, f1 = 1;
    in >> n;
    fibDataType k = 0;
    in >> k;
    if (!n || n == 1)
    {
        out << 1 << "\n";
        return;
    }
    for(fibDataType i = 2; i <= n; ++i)
    {
        sum = (f0 + f1) % powerOfTen[k];
        if (i & 1ULL)
            f0 = sum;
        else
            f1 = sum;
    } 
    out << sum % powerOfTen[k] << "\n";
}

int main(int argc, char** argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testParenthesisChecker();
    else
        fibCheckerWrapper(std::cin, std::cout);
    std::cout << "\n";
}
