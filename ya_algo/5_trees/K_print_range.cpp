/*struct Node {  
  const Node* left = nullptr;  
  const Node* right = nullptr;  
  int value;  
};*/ 

#include "solution.h"
#include <cassert>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

const int INF = -1e9;
using DataType = int32_t;
using VecType = vector<DataType>;

inline bool inRange(DataType nodeValue, int l, int r)
{
    return nodeValue <= r && nodeValue >= l;
}

void TreeLMRWalker(const Node* node, VecType& image, const int l, const int r)
{
    bool valueIsInRange = inRange(node->value, l, r);
    if (!node->left && !node->right && valueIsInRange)
    {
        std::cout << node->value << "\n";
        return;
    }

    if (node->left && (valueIsInRange || node->value >= r))
        TreeLMRWalker(node->left, image, l, r);

    if (valueIsInRange)
        std::cout << node->value << "\n";

    if (node->right && (valueIsInRange || node->value <= l))
        TreeLMRWalker(node->right, image, l,r);
}

bool TreeIsEmpty(const Node* root)
{
    return !root->left && !root->right;
} 

void print_range(Node* root, int l, int r) {
    if (TreeIsEmpty(root))
    {
        if (inRange(root->value, l, r))
        {
            std::cout << root->value << std::endl;
            return;
        }
    }
    VecType image;
    image.reserve(10000);
    if (root->value > r)
    {
        // Только влево 
        TreeLMRWalker(root->left, image, l, r);
    }
    else if (root->value < l)
    {
        // Только вправо
        TreeLMRWalker(root->right, image, l, r);
    }
    else
    {
        // В обе
        TreeLMRWalker(root->left, image, l, r);
        if (inRange(root->value, l, r))
            std::cout << root->value << std::endl;
        TreeLMRWalker(root->right, image, l, r);
    }
}

void test1() {
    Node node1({nullptr, nullptr, 2});
    Node node2({nullptr, &node1, 1});
    Node node3({nullptr, nullptr, 8});
    Node node4({nullptr, &node3, 8});
    Node node5({&node4, nullptr, 9});
    Node node6({&node5, nullptr, 10});
    Node node7({&node2, &node6, 5});
    print_range(&node7, 2, 8);
    // expected output: 2 5 8 8
}
/*
int main()
{
    test1();
}*/
