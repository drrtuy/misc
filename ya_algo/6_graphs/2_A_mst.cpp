//52228143 
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <numeric>

// Задача сводится к построению максимального остовного дерева.
// MST строил используя алгоритм Прима с priority_queue.
// Сложность по времени O(V * LOG(E)), по памяти O(V + E).

void MSTWrapper(std::istream& in, std::ostream& out);

void MSTTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    MSTWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void MSTTestWrapper()
{
    TestInputType input = { "4 4\n1 2 5\n1 3 6\n2 4 8\n3 4 3\n" };
    std::string expected = "19\n";
    MSTTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "3 3\n1 2 1\n1 2 2\n2 3 1\n" };
    expected = "3\n";
    MSTTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "2 0\n" };
    expected = "Oops! I did it again\n";
    MSTTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";
}

using DataType = uint32_t;
using VertexId = DataType;
using Weight = DataType;
// начало, конец, вес
using Edge = std::tuple<VertexId, VertexId, Weight>;

// Компаратор для отношения нестрого порядка по неубыванию весов рёбер.
struct EdgeComparator
{
    bool operator()(const Edge& lhs, const Edge& rhs)
    {
        return std::get<2>(lhs) <= std::get<2>(rhs);
    }
};

using SpanningTree = std::vector<Edge>;
using EdgeVector = SpanningTree;
using AvailableEdgesList = std::priority_queue<Edge, EdgeVector, EdgeComparator>;
using AdjacencyList = std::vector<std::pair<DataType, DataType>>;
using AdjacencyMatrix = std::vector<AdjacencyList>;
enum VisitedStatusEnum { visited, not_yet, };
using VerticesVisitedStatus = std::vector<VisitedStatusEnum>;

void addVertex(AdjacencyMatrix& adjMatrix, const VertexId v,
               AvailableEdgesList& edges, VerticesVisitedStatus& nonVisitedYetVertices,
               DataType& visitedVerticesCount)
{
    ++visitedVerticesCount;
    nonVisitedYetVertices[v] = visited;
    for (auto [edgeEnd, weight] : adjMatrix[v])
    {
        if (nonVisitedYetVertices[edgeEnd] == not_yet)
           edges.push({v, edgeEnd, weight});
    }
}

inline bool hasNotVisitedVertices(const DataType visitedVerticesCount, const DataType verticesInGraph)
{
    return visitedVerticesCount != verticesInGraph;
}

void MSTWrapper(std::istream& in, std::ostream& out)
{
    DataType n, nE, u, v, w;
    in >> n;
    in >> nE;
    AdjacencyMatrix adjMatrix(n + 1, AdjacencyList());
 
    for (size_t i = 0; i < nE; ++i)
    {
        in >> u;
        in >> v;
        in >> w;
        adjMatrix[u].push_back({v, w});
        adjMatrix[v].push_back({u, w});
    }
    uint32_t MSTCost = 0;
    VerticesVisitedStatus nonVisitedYetVertices(n + 1, not_yet);
    nonVisitedYetVertices[0] = visited;
    AvailableEdgesList edges;

    VertexId initialV = 1;
    DataType visitedVerticesCount = 0;
    addVertex(adjMatrix, initialV, edges, nonVisitedYetVertices, visitedVerticesCount);
    
    while (hasNotVisitedVertices(visitedVerticesCount, n) && !edges.empty())
    {
        auto [edgeStart, edgeEnd, edgeWeight] = edges.top();
        edges.pop();
        if (nonVisitedYetVertices[edgeEnd] == not_yet)
        {
            MSTCost += edgeWeight;
            addVertex(adjMatrix, edgeEnd, edges, nonVisitedYetVertices, visitedVerticesCount);
        }
    }

    if (hasNotVisitedVertices(visitedVerticesCount, n))
        out << "Oops! I did it again" << std::endl;
    else
        out << MSTCost << std::endl;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        MSTTestWrapper();
    else
        MSTWrapper(std::cin, std::cout);
    std::cout << "\n";
}
