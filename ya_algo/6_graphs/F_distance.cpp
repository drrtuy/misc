#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <queue>
#include <iterator>

void DistanceWrapper(std::istream& in, std::ostream& out);

void DistanceTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    DistanceWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void DistanceTestWrapper()
{
    TestInputType input = { "5 5\n2 4\n3 5\n2 1\n2 3\n4 5\n1 5\n" };
    std::string expected = "3\n";
    DistanceTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "4 3\n2 3\n4 3\n2 4\n1 3\n" };
    expected = "-1\n";
    DistanceTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "2 1\n2 1\n1 1\n" };
    expected = "0\n";
    DistanceTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";
}

enum Colors { white, grey, black };
using DataType = uint32_t;
using VertexId = DataType;
using VertexVector = std::vector<VertexId>;
using Map = std::vector<VertexVector>;
using ColorStates = std::vector<Colors>;


void DistanceWrapper(std::istream& in, std::ostream& out)
{
    DataType n, m;
    in >> n;
    in >> m;
    Map map(n + 1);

    // Создаём списки смежности
    for (DataType i = 1; i <= m; ++i)
    {
        DataType edgeStart, edgeEnd;
        in >> edgeStart;
        in >> edgeEnd;
        map[edgeStart].push_back(edgeEnd);
        map[edgeEnd].push_back(edgeStart);
    }

    VertexId pathStart, pathEnd;
    in >> pathStart;
    in >> pathEnd;

    if (pathStart == pathEnd)
    {
        out << "0\n";
        return;
    }

    std::queue<DataType> vertexQueue;
    ColorStates colors(n + 1, white);
    std::vector<DataType> distance(n + 1, 0);
    // BFS
    vertexQueue.push(pathStart);
    while (!vertexQueue.empty())
    {
        VertexId vertex = vertexQueue.front();
        vertexQueue.pop();
        for (auto endPoint: map[vertex])
        {
            if (colors[endPoint] == white)
            {
                distance[endPoint] = distance[vertex] + 1;
                if (endPoint == pathEnd)
                {
                    out << distance[endPoint] << std::endl;
                    return;
                }
                colors[endPoint] = grey;
                vertexQueue.push(endPoint);
            }
        }
        colors[vertex] = black;
    }
    out << "-1\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        DistanceTestWrapper();
    else
        DistanceWrapper(std::cin, std::cout);
    std::cout << "\n";
}
