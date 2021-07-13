#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stack>
#include <queue>

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
    TestInputType input = { "6 3\n1 2\n6 5\n2 3\n" };
    std::string expected = "3\n1 2 3 \n4 \n5 6 \n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "6 3\n1 2\n4 5\n1 6\n" };
    expected = "3\n1 2 6 \n3 \n4 5 \n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "6 3\n1 4\n6 3\n5 2\n" };
    expected = "3\n1 4 \n2 5 \n3 6 \n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "2 0\n" };
    expected = "2\n1 \n2 \n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "4 3\n2 3\n2 1\n4 3\n" };
    expected = "1\n1 2 3 4 \n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "10 7\n2 1\n5 8\n5 3\n9 6\n1 9\n6 10\n7 2\n" };
    expected = "3\n1 2 6 7 9 10 \n3 5 8 \n4 \n";
    DFSTest(input, expected);
    input.clear();
    expected.clear();
}


enum Colors { white, grey, black };
using DataType = int32_t;
using Matrix = std::vector<std::vector<DataType>>;
using ColorStates = std::vector<Colors>; 

void DFSWrapper(std::istream& in, std::ostream& out)
{
    DataType n, nE, u, v;
    in >> n;
    in >> nE;
    Matrix m(n);
    std::vector<DataType> colors(n + 1, -1);
 
    for (DataType i = 0; i < nE; ++i)
    {
        in >> u;
        in >> v;
        m[u - 1].push_back(v);
        m[v - 1].push_back(u);
    }

    // sort edge endpoints
    //for (auto& row : m)
    //    std::sort(row.begin(), row.end(), std::greater<DataType>());

    // aux colors grey = 0, white = -1;
    DataType componentCount = 1;
    std::stringstream ss;
    for (size_t startingVertex = 1; startingVertex <= colors.size(); ++startingVertex)
    {
        if (colors[startingVertex] != -1)
            continue;
        //std::priority_queue<DataType, std::vector<DataType>, std::greater<DataType>> vertexStack;
        std::stack<DataType> vertexStack;
        std::vector<DataType> intBuffer;
        // DFS
        vertexStack.push(startingVertex);
        while (!vertexStack.empty())
        {
            DataType vertex = vertexStack.top();
            vertexStack.pop();
            if (colors[vertex] == -1)
            {
                //ss << vertex << " ";
                colors[vertex] = 0; // grey
                vertexStack.push(vertex);
                for (auto edgeEnd : m[vertex - 1])
                {
                    if (colors[edgeEnd] == -1)
                        vertexStack.push(edgeEnd);
                }
            }
            else if (colors[vertex] == 0)
            {
                colors[vertex] = componentCount;
                intBuffer.push_back(vertex); 
                //ss << vertex << " ";
            }
        }
        std::sort(intBuffer.begin(), intBuffer.end(), std::less<DataType>());
        std::copy(intBuffer.begin(), intBuffer.end(), std::ostream_iterator<DataType>(ss, " ")); 
        ss << "\n";
        ++componentCount;
        intBuffer.clear();
    }
    out << componentCount - 1 << "\n";
    out << ss.str();
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
