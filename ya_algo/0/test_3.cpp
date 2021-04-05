#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using int16_t = short int;
using uint16_t = unsigned short int;

struct Node
{
    uint16_t n,
    int16_t val,
    Node* left,
    Node* right,
};

using vector<Node*> = NodeVector;
using vector<vector<decltype Node::val>> = LevelMembers;

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
        node->left = nullptr;
        node->right = nullptr;
        nodeVector[it] = node;
    }

    oFile << "\n";
    oFile.close();
    iFile.close();
}
