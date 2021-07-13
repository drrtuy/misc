// 52076558 
/*struct Node {  
  Node* left = nullptr;  
  Node* right = nullptr;  
  int value;  
};*/ 

// Сложность исполнения O(logN), т.к. мы тратим O(log H)(где log H, высота удаляемого узла) на то, чтобы найти
// удаляемый узел и e(log R) в худшем случае на то, чтобы найти замену. Сложность операции замены O(C).
// Алгоритм не потребляет доп. памяти.
// Для прохода по дереву пользовался циклом, а не рекурсией.

#include "solution.h"
#include <cassert>
#include <utility>
using namespace std;

const int INF = -1e9;
using DataType = int;
using NodeAndParent = std::pair<Node*,Node*>; 

NodeAndParent findTarget(Node* root, DataType key)
{
    Node* currNode = root;
    Node* currNodeParent = nullptr;
    while (currNode && currNode->value != key)
    {
        currNodeParent = currNode;
        if (currNode->value > key)
            currNode = currNode->left;
        else
            currNode = currNode->right;
    }
    return (currNode && currNode->value == key)
            ? NodeAndParent(currNode, currNodeParent)
            : NodeAndParent(nullptr, nullptr);
}

typedef enum { left, right } Direction;

inline void replaceChild(Node* parent, Node* child, Node* replacement)
{
    if (parent->left && parent->left == child)
        parent->left = replacement;
    else
        parent->right = replacement;
}

inline Node* connectRootsChildWithReplacement(const bool replIsRootsChild,
                                              Node* target,
                                              Node* replacement,
                                              const Direction d)
{
    if (replIsRootsChild && d == left)
        replacement->right = target->right;
    // Не проверяем для правого аргумента т.к. в этой ветке проиходит замена корня без левого поддерева ребёнком справа
    return replacement;
}

Node* swapNodesOnDelete(Node* root, const NodeAndParent& targetAndParent, const Direction d)
{
    Node* target = targetAndParent.first;
    Node* targetParent = targetAndParent.second;
    Node* replacement = nullptr;
    Node* replacementParent = nullptr;

    if (d == left)
    {
        replacement = target->left;
        while (replacement->right)
        {
            replacementParent = replacement;
            replacement = replacement->right;
        }
    }
    else
    {
        replacement = target->right;
        while (replacement->left)
        {
            replacementParent = replacement;
            replacement = replacement->left;
        }
    }
    
    // Замена не является потомком цели
    if (replacementParent)
    {
        if (d == left)
            replacementParent->right = replacement->left;
        else
            replacementParent->left = replacement->right;

        replacement->left = target->left;
        replacement->right = target->right;
    }
    else
    {
        if (d == left)
            replacement->right = target->right;
        else
            replacement->left = target->left;
    }

    if (targetParent)
    {
        replaceChild(targetParent, target, replacement);
        return root;
    }
    else
        return connectRootsChildWithReplacement(!replacementParent, target, replacement, d); // замена корня
}

inline bool targetHasLeftChild(const NodeAndParent& targetAndParent)
{
    return targetAndParent.first->left;
}

inline bool targetNotFound(const NodeAndParent& targetAndParent)
{
    return !targetAndParent.first;
}

inline bool targetHasNoChildren(const NodeAndParent& targetAndParent)
{
    return !targetAndParent.first->left && !targetAndParent.first->right;
}

inline bool targetIsRoot(const NodeAndParent& targetAndParent)
{
    return !targetAndParent.second;
}

Node* remove(Node* root, int key)
{
    NodeAndParent targetAndParent = findTarget(root, key);
    if (targetNotFound(targetAndParent))
        return root;

    if (targetHasNoChildren(targetAndParent))
    {
        if (targetIsRoot(targetAndParent))
            return nullptr;
        else
        {
            replaceChild(targetAndParent.second, targetAndParent.first, nullptr);
            return root;
        }
    }

    return targetHasLeftChild(targetAndParent)
        ? swapNodesOnDelete(root, targetAndParent, left)
        : swapNodesOnDelete(root, targetAndParent, right);
}
/*
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}
int main()
{
    test();
}*/
