//52197640
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <stack>

// Сеть дорог представляем орграфом, где тип дороги, соединяющей города
// становится направлением: R - от меньшего к бОльшему, B - наоборот.
// Тогда исходная задача сводится к поиску цикла в заданном таким образом
// графе.
// Сложность DFS-обхода графа с поиском цикла по времени O(V + E),
// сложность по памяти O(V ^ 2).

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
using ColorStates = std::vector<Colors>;

bool DFSWalk(const Map& map, ColorStates& colors, const VertexId from)
{
    VertexStack vertexStack;
    vertexStack.push(from);
    while (!vertexStack.empty())
    {
        DataType vertex = vertexStack.top();
        vertexStack.pop();
        if (colors[vertex] == white)
        {
            colors[vertex] = grey;
            vertexStack.push(vertex);
            for (auto edgeEnd : map[vertex])
            {
                if (colors[edgeEnd] == white)
                    vertexStack.push(edgeEnd);
                if (colors[edgeEnd] == grey)
                    return true;
            }
        } 
        else if (colors[vertex] == grey)
            colors[vertex] = black;
    }
    return false;
}

bool mapHasLoops(const Map& map)
{
    ColorStates colors(map.size() + 1, white);
    for (VertexId v = 1; v < map.size(); ++v)
    {
        if (colors[v] == white && DFSWalk(map, colors, v))
            return true;
    }
    return false;
}

void ConnectedGWrapper(std::istream& in, std::ostream& out)
{
    DataType n;
    char roadType;
    in >> n;
    Map map(n + 1);

    for (size_t i = 1; i < map.size(); ++i)
        map[i].reserve(n - i);

    // Создаём верхнетреугольную матрица смежности.
    for (VertexId i = 1; i < n; ++i)
    {
        for (VertexId it = i + 1; it <= n; ++it)
        {
            in >> roadType;
            if ((RoadConnectionTypes)roadType == R)
                map[i].push_back(it);
            else
                map[it].push_back(i);
        }
    }

    if (mapHasLoops(map))
        out << "NO" << std::endl;
    else
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
