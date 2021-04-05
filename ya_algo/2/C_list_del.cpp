#include "solution.h"

Node* solution(Node* head, int idx)
{
    if (!idx)
        return head->next;

    Node* node = head;
    Node* prevNode = nullptr;

    while(node && idx-- > 0)
    {
        prevNode = node;
        node = node->next;
    }
   
    prevNode->next = node->next;
    
    return head;
}
