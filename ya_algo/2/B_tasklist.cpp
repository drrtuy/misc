#include "solution.h"

void solution(Node* head)
{
    Node* node = head;
    while(node)
    {
        std::cout << node->value << "\n"; 
        node = node->next;
    }
}
