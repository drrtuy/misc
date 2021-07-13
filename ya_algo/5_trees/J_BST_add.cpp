/*struct Node {  
  Node* left;  
  Node* right;
  int value;
};*/


#include "solution.h"
#include <cassert>

void recursion(Node* node, int key)
{
    if (key < node->value)
    {
        if (!node->left)
        {
            node->left = new Node{nullptr, nullptr, key};
            return;
        }
        recursion(node->left, key);
        return;
    }
    
    if (!node->right)
    {
        node->right = new Node{nullptr, nullptr, key};
        return;
    }
    recursion(node->right, key);
}

Node* insert(Node* root, int key) {
    if (!root)
    {
        Node* newRoot = new Node{nullptr, nullptr, key};
        return newRoot;
    }

    recursion(root, key);
    return root;
}
/*
void test() {
    Node node1({nullptr, nullptr, 7});
    Node node2({&node1, nullptr, 8});
    Node node3({nullptr, &node2, 7});
    Node* newHead = insert(&node3, 6);
    assert(newHead->left->value == 6);
    assert(newHead == &node3);
}

int main()
{
    test();
}*/
