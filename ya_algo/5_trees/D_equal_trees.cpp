/*struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;  
}; 
*/
#include "solution_tree.h"
#include <cassert>
#include <string>

using namespace std;

const int INF = -1e9;

std::string& TreeWalkerLeft(const Node* node, std::string& image)
{
    if (!node->left && !node->right)
    {
        image.append(std::to_string(node->value));
        return image;
    }

    if (node->left)
        TreeWalkerLeft(node->left, image);
    else
        image.append(" ");
    if (node->right)
        TreeWalkerLeft(node->right, image);
    else
        image.append(" ");
    image.append(std::to_string(node->value));
    return image;
}

bool TreeIsEmpty(const Node* root)
{
    return !root->left && !root->right;
} 

bool Solution(const Node* root1, const Node* root2) {
    if (TreeIsEmpty(root1) && TreeIsEmpty(root2))
        return root1->value == root2->value;
    std::string image1;
    std::string image2;
    return TreeWalkerLeft(root1, image1) == TreeWalkerLeft(root2, image2);
} 

void test() {

    Node node1({1, nullptr, nullptr});
    Node node2({2, nullptr, nullptr});
    Node node3({3, &node1, &node2});

    Node node4({1, nullptr, nullptr});
    Node node5({2, nullptr, nullptr});
    Node node6({3, &node4, &node5});
    assert(Solution(&node3, &node6));

    node1 = Node({1, nullptr, nullptr});
    node2 = Node({2, &node1, nullptr});

    node3 = Node({1, nullptr, nullptr});
    node4 = Node({2, nullptr, &node3});
    assert(Solution(&node2, &node4) == false);
    node1 = Node({1, nullptr, nullptr});
    node2 = Node({2, nullptr, nullptr});
    assert(Solution(&node1, &node2) == false);
}
/*
int main()
{
    test();
}*/
