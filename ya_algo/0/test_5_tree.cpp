#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;
using int16_t = short int;
using uint16_t = unsigned short int;

class Node
{
  public:
    Node(): leftId(-1), rightId(-1), left(nullptr), right(nullptr) {}
    uint16_t n;
    int16_t val;
    int16_t leftId;
    int16_t rightId;
    Node* left;
    Node* right;

    friend std::ostream& operator<<(std::ostream& os, const Node& obj);
};

struct avgInfo
{
    avgInfo(): count(0), sum(0) {}
    uint16_t count;
    int32_t sum;
};

std::ostream& operator<<(std::ostream& os, const Node& obj)
{
    os << "N: " << obj.n << " val: " << obj.val << " leftId: " << obj.leftId
        << " rightId: " << obj.rightId << " left: " << (unsigned long long)obj.left
        << " right: " << (unsigned long long) obj.right << "\n";
    return os;
}

using NodeVector = vector<Node*>;
using LevelInfo = vector<avgInfo>;


void dFSPreOrderTraverse(Node* currentNode, uint16_t level, LevelInfo& levelInfo)
{
//    cout << "currentNode " << (unsigned long long)currentNode << "\n"; 
    if (!currentNode)
        return;
   
//    cout << "currentNode->n: " << currentNode->n << "\n"; 
    levelInfo[level].count++;
    levelInfo[level].sum += currentNode->val;

    dFSPreOrderTraverse(currentNode->left, level + 1, levelInfo);
    dFSPreOrderTraverse(currentNode->right, level + 1, levelInfo);
}

int main()
{
    ios_base::sync_with_stdio(false);
    ifstream iFile("input.txt");
    ofstream oFile("output.txt");

    uint32_t N = 0;
    uint32_t buf = 0;
    iFile >> N;

    // parse the tree
    NodeVector nodeVector(N + 1);
    for (uint16_t it = 1; it <= N; it++) {
        Node* node = new Node();
        iFile >> node->n;
        iFile >> node->val;
        iFile >> node->leftId;
        iFile >> node->rightId;
        //cout << *node << "\n";
        nodeVector[node->n] = node;
    }

    // Build the tree
    for (uint16_t it = 1; it <= N; it++) {
        Node* node = nodeVector[it];
        if (node->leftId != -1 && !node->left)
            node->left = nodeVector[node->leftId]; 

        if (node->rightId != -1 && !node->right)
            node->right = nodeVector[node->rightId]; 
        //cout << *node << "\n";
    }
    
    // too lazy to size it dynamically
    LevelInfo levelInfo(N);
    dFSPreOrderTraverse(nodeVector[1], 0, levelInfo);
    for (auto& level: levelInfo) {
//        cout << "level.sum: " << level.sum << " level.count " << level.count << "\n";
        if (level.count) {
            cout << std::fixed << setprecision(2) << (float)level.sum / (float)level.count << " ";
            oFile << std::fixed << setprecision(2) << (float)level.sum / (float)level.count << " ";
        }
    }
    cout << "\n";

    // clean up
    oFile << "\n";
    oFile.close();
    iFile.close();

    for (uint16_t it = 1; it <= N; it++) {
        delete nodeVector[it];
    }
}
