#include "solution.h"

int solution(Node *head, const std::string& elem)
{
    int idx = 0;

    if (head->value == elem)
    {
        return idx;
    }

    Node* node = head;
    bool found = false;
    while(node && !(found = node->value == elem))
    {
        node = node->next;
        ++idx;
    }
  
    if (!found)
        return -1;
   
    return idx; 
}
