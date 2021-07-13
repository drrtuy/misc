
/*struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;  
};  
*/

#include "solution_tree.h"
#include <cassert>
#include <iostream>

using namespace std;

uint32_t sum = 0;

void recursion(const Node* node, uint32_t pathNumber)
{
    pathNumber *= 10;
    pathNumber += node->value;
    if (!node->left && !node->right)
    {
        sum += pathNumber;
        return;
    }
    if (node->left)
        recursion(node->left, pathNumber);
    if (node->right)
        recursion(node->right, pathNumber);
}


int Solution(const Node* root) {
    recursion(root, 0);
    return sum;
} 

/*
void test() {
    Node node1({2, nullptr, nullptr});
    Node node2({1, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({2, nullptr, nullptr});
    Node node5({1, &node4, &node3});
    assert(Solution(&node5) == 275);
}

int main()
{
    test();
}
*/
