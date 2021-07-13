#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <numeric>

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

/*
    input = { "2 0\n" };
    expected = "2\n1 \n2 \n";
    MSTTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "4 3\n2 3\n2 1\n4 3\n" };
    expected = "1\n1 2 3 4 \n";
    MSTTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "10 7\n2 1\n5 8\n5 3\n9 6\n1 9\n6 10\n7 2\n" };
    expected = "3\n1 2 6 7 9 10 \n3 5 8 \n4 \n";
    MSTTest(input, expected);
    input.clear();
    expected.clear();
*/
}

using DataType = uint32_t;
using VertexId = DataType;
using Edge = std::tuple<DataType, DataType, DataType>;

struct EdgeComparator
{
    bool operator()(const Edge& lhs, const Edge& rhs)
    {
        return std::get<2>(lhs) >= std::get<2>(rhs);
    }
};

using SpanningTree = std::vector<Edge>;
using EdgeVector = SpanningTree;
using AvailableEdgesList = std::priority_queue<Edge, EdgeVector, EdgeComparator>;
using AdjacencyList = std::vector<std::pair<DataType, DataType>>;
using AdjacencyMatrix = std::vector<AdjacencyList>;
using VerticesSet = std::unordered_set<DataType>;
using VerticesSetHelperVec = std::vector<DataType>;

void addVertex(AdjacencyMatrix& adjMatrix, const VertexId v, AvailableEdgesList& edges, VerticesSet& addedVertices,
               VerticesSet& nonAddedYetVertices)
{
    (void)addedVertices.insert(v);
    (void)nonAddedYetVertices.erase(v);
    for (auto [edgeEnd, weight] : adjMatrix[v - 1])
    {
        if (addedVertices.find(edgeEnd) == addedVertices.end())
           edges.push({v, edgeEnd, weight});
    }
}

void MSTWrapper(std::istream& in, std::ostream& out)
{
    DataType n, nE, u, v, w;
    in >> n;
    in >> nE;
    AdjacencyMatrix adjMatrix(n, AdjacencyList());
 
    for (size_t i = 0; i < nE; ++i)
    {
        in >> u;
        in >> v;
        in >> w;
        adjMatrix[u - 1].push_back({v, w});
        adjMatrix[v - 1].push_back({u, w});
    }
    uint32_t MSTCost = 0;
    VerticesSet addedVertices(n);
    VerticesSetHelperVec helperVec(n);
    std::iota(helperVec.begin(), helperVec.end(), 1);
    VerticesSet nonAddedYetVertices(helperVec.begin(), helperVec.end(), n);
    AvailableEdgesList edges;

    VertexId initialV = *nonAddedYetVertices.begin();
    addVertex(adjMatrix, initialV, edges, addedVertices, nonAddedYetVertices);
    
    while (!nonAddedYetVertices.empty() && !edges.empty())
    {
        auto [edgeStart, edgeEnd, edgeWeight] = edges.top();
        edges.pop();
        if (addedVertices.find(edgeEnd) == addedVertices.end())
        {
            MSTCost += edgeWeight;
            addVertex(adjMatrix, edgeEnd, edges, addedVertices, nonAddedYetVertices);
        }
    }

    if (!nonAddedYetVertices.empty())
        out << "Oops! I did it again";
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
