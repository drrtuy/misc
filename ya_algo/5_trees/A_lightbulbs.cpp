/*
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;  
};  */
#include "solution_tree.h"
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

const int INF = -1e9;
int result;

void TreeWalker(const Node* node)
{
    result = node->value > result ? node->value : result;
    if (!node->left && !node->right)
        return;

    if (node->left)
        TreeWalker(node->left);
    if (node->right)
        TreeWalker(node->right);
}

int Solution(const Node* root) {
    TreeWalker(root);
    return result;
}

void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({2, &node3, nullptr});
    assert(Solution(&node4) == 3);
}
