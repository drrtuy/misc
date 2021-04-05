// Contest test run ID 48228488
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

void transposeWrapper(std::istream& in, std::ostream& out);

void testTranspose()
{
    std::stringstream in;
    in << "4\n";
    in << "3\n";
    in << "1 2 3\n";
    in << "0 2 6\n";
    in << "7 4 1\n";
    in << "2 7 0\n";
    std::stringstream ss;
    transposeWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "1 0 7 2 \n2 2 4 7 \n3 6 1 0 \n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "1\n";
    in << "3\n";
    in << "1 2 1\n";
    transposeWrapper(in, ss);
    out = ss.str();
    assert(out == "1 \n2 \n1 \n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "3\n";
    in << "1\n";
    in << "1\n";
    in << "2\n";
    in << "3\n";
    transposeWrapper(in, ss);
    out = ss.str();
    assert(out == "1 2 3 \n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "9\n";
    in << "5\n";
    in << "-7 -1 0 -4 -9\n";
    in << "5 -1 2 2 9\n";
    in << "3 1 -8 -1 -7\n";
    in << "9 0 8 -8 -1\n";
    in << "2 4 5 2 8\n";
    in << "-7 10 0 -4 -8\n";
    in << "-3 10 -7 10 3\n";
    in << "1 6 -7 -5 9\n";
    in << "-1 9 9 1 9\n";
    transposeWrapper(in, ss);
    out = ss.str();
    assert(out == "-7 5 3 9 2 -7 -3 1 -1 \n-1 -1 1 0 4 10 10 6 9 \n0 2 -8 8 5 0 -7 -7 9 \n-4 2 -1 -8 2 -4 10 -5 1 \n-9 9 -7 -1 8 -8 3 9 9 \n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "1\n";
    in << "1\n";
    in << "-1\n";
    transposeWrapper(in, ss);
    out = ss.str();
    assert(out == "-1 \n");
}

using MatrixElT = int16_t;
using Matrix = std::vector<std::vector<MatrixElT>>;

void transpose(const Matrix& m, std::ostream& out)
{
    size_t xSize = m[0].size();
    size_t ySize = m.size();
    for (size_t Xpos = 0; Xpos < xSize; ++Xpos)
    {
        for (size_t Ypos = 0; Ypos < ySize; ++Ypos)
        {
            out << m[Ypos][Xpos] << " ";
        }
        out << "\n";
    }
}

void transposeWrapper(std::istream& in, std::ostream& out)
{
    uint16_t n = 0;
    uint16_t m = 0;
    in >> n; in >> m;
    if (!n || !m)
        return;
    uint16_t mSize = m - 1; 
    uint16_t nSize = n - 1; 
    Matrix matrix(n);
        for(auto& v: matrix)
            v.reserve(m);

    MatrixElT buf;

    for (size_t y = 0; y <= nSize; ++y)
    {
        for (size_t x = 0; x <= mSize; ++x)
        {
            in >> buf;
            matrix[y].push_back(buf);
        }
    }
    transpose(matrix, out);
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testTranspose();
    else
        transposeWrapper(std::cin, std::cout);
    std::cout << "\n";
}
