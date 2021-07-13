/*struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;  
};*/ 

#include "solution_tree.h"
#include <cassert>
#include <string>
#include <vector>

using namespace std;

const int INF = -1e9;
bool isBSTTree = true;
using DataType = int32_t;
using VecType = vector<DataType>;

void checkInvarianceAddToImage(const Node* node, VecType& image)
{
    if (!image.empty())
        isBSTTree = node->value > image.back();
    if (isBSTTree)
        image.push_back(node->value);
}

void TreeLMRWalker(const Node* node, VecType& image)
{
    if (!isBSTTree)
        return;

    if (!node->left && !node->right)
        return checkInvarianceAddToImage(node, image);

    if (isBSTTree && node->left)
        TreeLMRWalker(node->left, image);

    if (isBSTTree)
        checkInvarianceAddToImage(node, image);

    if (isBSTTree && node->right)
        TreeLMRWalker(node->right, image);
}

bool TreeIsEmpty(const Node* root)
{
    return !root->left && !root->right;
} 

bool Solution(const Node* root) {
    if (TreeIsEmpty(root))
        return true;
    VecType image;
    TreeLMRWalker(root, image);
    return isBSTTree;
} 

void test() {
    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(!Solution(&node5));
    }
}
/*
int main()
{
    test();
}*/
