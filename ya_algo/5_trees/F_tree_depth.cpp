/* Comment it before submitting
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;  
};  
*/
#include "solution_tree.h"
#include <cassert>
#include <cstdlib>

size_t maxDepth = 0;

using namespace std;

void recursion(const Node* n, size_t depth)
{
    maxDepth = ++depth > maxDepth ? depth : maxDepth;
    if (n->left)
        recursion(n->left, depth);
    if (n->right)
        recursion(n->right, depth);
}

int Solution(const Node* root) {
    recursion(root, 0);
    return maxDepth;
} 
/*
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({4, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({8, nullptr, nullptr});
    Node node5({5, &node3, &node4});
    assert(Solution(&node5) == 3);
}

int main()
{
    test();
}*/
