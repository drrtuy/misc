#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <stack>
#include <queue>
#include <unordered_set>
#include <algorithm>

void ConnectedGWrapper(std::istream& in, std::ostream& out);

void ConnectedGTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    ConnectedGWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void ConnectedGTestWrapper()
{
    TestInputType input = { "3\nRB\nR" };
    std::string expected = "NO\n";
    ConnectedGTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "4\nBBB\nRB\nB\n" };
    expected = "YES\n";
    ConnectedGTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";

    input = { "5\nRRRB\nBRR\nBR\nR" };
    expected = "NO\n";
    ConnectedGTest(input, expected);
    input.clear();
    expected.clear();
    std::cout << "\n";
}

enum Colors { white, grey, black };
enum RoadConnectionTypes { B = 66, R = 82 };
using DataType = uint32_t;
using VertexId = DataType;
using VertexVector = std::vector<VertexId>;
using Map = std::vector<VertexVector>;
using VertexStack = std::stack<VertexId>;
using VertexQueue = std::queue<VertexId>;
using ColorStates = std::vector<Colors>; 


bool findPathDFS(Map& map, const VertexId from, const VertexId to)
{
    VertexStack vertexStack;
    ColorStates colors(to - from + 3, white);
    //ColorStates colors(map.size() + 1, white);
    // ConnectedG
    vertexStack.push(from);
    while (!vertexStack.empty())
    {
        VertexId vertex = vertexStack.top();
        vertexStack.pop();
        VertexId vertexColorIdx = vertex - from + 1;
        if (colors[vertexColorIdx] == white)
        {
            colors[vertexColorIdx] = grey;
            for (auto edgeEnd : map[vertex - 1])
            {
                if (edgeEnd == to)
                    return true;
                if (edgeEnd > to || edgeEnd < from)
                    continue;
                VertexId edgeEndColorIdx = edgeEnd - from + 1;
                if (colors[edgeEndColorIdx] == white)
                {
                    vertexStack.push(edgeEnd);
                }
            }
        }
    }
    return false;
}

bool findPathBFS(Map& map, const VertexId from, const VertexId to)
{
    VertexQueue vertexQueue;
    ColorStates colors(to - from + 3, white);
    //ColorStates colors(map.size() + 1, white);
    // ConnectedG
    vertexQueue.push(from);
    while (!vertexQueue.empty())
    {
        DataType vertex = vertexQueue.front();
        vertexQueue.pop();
        for (auto edgeEnd: map[vertex])
        {
            if (edgeEnd > to || edgeEnd < from)
                continue;
            if (edgeEnd == to)
                return true;
            VertexId edgeEndColorIdx = edgeEnd - from + 1;
            if (colors[edgeEndColorIdx] == white)
            {
                colors[edgeEndColorIdx] = grey;
                vertexQueue.push(edgeEnd);
            }
        }
    }
    return false;
}

bool mapHasDirectPath(const Map& map, const VertexId from, const VertexId to)
{
    return std::binary_search(map[from].begin(), map[from].end(), to);
} 

void ConnectedGWrapper(std::istream& in, std::ostream& out)
{
    DataType n;
    char roadType;
    in >> n;
    Map m(n);
    Map mapR(n+1);
    Map mapB(n+1);

    for (size_t i = 1; i < mapR.size(); ++i)
    {
        mapR[i].reserve(n - i);
        mapB[i].reserve(n - i);
    }

    // Fill the maps
    for (VertexId i = 1; i < n; ++i)
    {
        for (VertexId it = i + 1; it <= n; ++it)
        {
            in >> roadType;
            if ((RoadConnectionTypes)roadType == R)
                mapR[i].push_back(it);
            else
                mapB[i].push_back(it);
        }
    }

    // Iterate over the vertexes pairs
    for (VertexId i = 1; i <= n - 1; ++i)
    {
        for (VertexId it = i + 1; it <= n; ++it)
        {
            bool mapHasDirectBPath = mapHasDirectPath(mapB, i, it);
            if (mapHasDirectBPath)
            {
                if (findPathBFS(mapR, i, it))
                {
                    std::cout << "FAIL " << std::to_string(i) << " " << std::to_string(it) << "\n";
                    out << "NO" << std::endl;
                    return;
                }
            }
            else // direct R path
            {
                if (findPathBFS(mapB, i, it))
                {
                    std::cout << "FAIL " << std::to_string(i) << " " << std::to_string(it) << "\n";
                    out << "NO" << std::endl;
                    return;
                }
            }

/*
            if (findPathDFS(mapR, i, it) && findPathDFS(mapB, i, it))
            {
                out << "NO" << std::endl;
                return;
            }
*/
        }
    }
    out << "YES" << std::endl;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        ConnectedGTestWrapper();
    else
        ConnectedGWrapper(std::cin, std::cout);
    std::cout << "\n";
}
