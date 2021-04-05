#include "solution.h"

Node* solution(Node* head)
{
    if (!head->next)
    {
        return head;
    }

    Node* node = head;
    Node* tmp = nullptr;
    while(node->next)
    {
        tmp = node->next;
        node->next = node->prev;
        node->prev = tmp;
        node = tmp;
    }

    tmp = node->next;
    node->next = node->prev;
    node->prev = tmp; 
  
    return node;
}
