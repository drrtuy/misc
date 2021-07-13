/*struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;  
};*/  
#include "solution_tree.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

const int INF = -1e9;
bool treeIsBalanced = true;

using DataType = int;

DataType TreeWalker(const Node* node)
{
    if (!treeIsBalanced || (!node->left && !node->right))
        return 0;

    DataType leftHeight = treeIsBalanced && node->left ? TreeWalker(node->left) + 1 : 0;
    DataType rightHeight = treeIsBalanced && node->right ? TreeWalker(node->right) + 1 : 0;

    if ((leftHeight || rightHeight) && abs(rightHeight - leftHeight) > 1)
        treeIsBalanced = false;

    return max(leftHeight, rightHeight);
}

bool Solution(const Node* root) {
    TreeWalker(root);
    return treeIsBalanced;
}

void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, &node1});
    Node node3({3, nullptr, &node2});
    assert(Solution(&node3) == false);
    treeIsBalanced = true;
    node1 = Node({1, nullptr, nullptr});
    node2 = Node({-5, &node1, nullptr});
    node3 = Node({3, nullptr, nullptr});
    Node node4({3, &node2, &node3});
    Node node5 ({3, nullptr, nullptr});
    Node node6({3, &node5, &node4});
    assert(Solution(&node6) == false);
    treeIsBalanced = true;
    node1 = Node({1, nullptr, nullptr});
    node2 = Node({-5, nullptr, nullptr});
    node3 = Node({3, &node1, &node2});
    assert(Solution(&node3) == true);
}
/*
int main()
{
    test();
}*/
