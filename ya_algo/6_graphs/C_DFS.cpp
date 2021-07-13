#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stack>

void DFSWrapper(std::istream& in, std::ostream& out);

void DFSTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    DFSWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void DFSTestWrapper()
{
    TestInputType input = { "4 4\n3 2\n4 3\n1 4\n1 2\n3\n",};
    std::string expected = "3 2 1 4 \n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();

    input = { "2 1\n1 2\n1\n" };
    expected = "1 2 \n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();

/*
    input = { "123\n", "100003\n", "HaSH" };
    expected = "56156\n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();
*/
}


enum Colors { white, grey, black };
using DataType = uint32_t;
using Matrix = std::vector<std::vector<DataType>>;
using ColorStates = std::vector<Colors>; 

void DFSWrapper(std::istream& in, std::ostream& out)
{
    DataType n, nV, u, v, startingVertex;
    in >> n;
    in >> nV;
    Matrix m(n);
    ColorStates colors(n + 1, white);
 
    for (size_t i = 0; i < nV; ++i)
    {
        in >> u;
        in >> v;
        m[u - 1].push_back(v);
        m[v - 1].push_back(u);
    }
    in >> startingVertex;

    // sort edge endpoints
    for (auto& row : m)
        std::sort(row.begin(), row.end(), std::greater<DataType>());

    std::stack<DataType> vertexStack;
    // DFS
    vertexStack.push(startingVertex);
    while (!vertexStack.empty())
    {
        DataType vertex = vertexStack.top();
        vertexStack.pop();
        if (colors[vertex] == white)
        {
            out << vertex << " ";
            colors[vertex] = grey;
            vertexStack.push(vertex);
            for (auto edgeEnd : m[vertex - 1])
            {
                if (colors[edgeEnd] == white)
                    vertexStack.push(edgeEnd);
            }
        } 
        else if (colors[vertex] == grey)
            colors[vertex] = black;
    }
    out << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        DFSTestWrapper();
    else
        DFSWrapper(std::cin, std::cout);
    std::cout << "\n";
}
