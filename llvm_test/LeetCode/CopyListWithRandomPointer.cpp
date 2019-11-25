#include <cstdlib>
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node root(0, NULL, NULL);
        /* 拷贝next */
        Node* p_head = head;
        Node* p_root = &root;
        while (p_head != NULL)
        {
            p_root->next = new Node(p_head->val, NULL, NULL);
            p_root = p_root->next;
            p_head = p_head->next;
        }
        /* 拷贝random */
        p_head = head;
        p_root = &root;
        Node* ptmp;
        while (p_head != NULL)
        {
            /* find random */
            if (p_head->random != NULL)
            {
                ptmp = root.next;
                while (ptmp != NULL)
                {
                    if (ptmp->val == p_head->random->val)
                        break;
                    ptmp=ptmp->next;
                }
                p_root->next->random = ptmp;
            }
            p_root = p_root->next;
            p_head = p_head->next;
        }
        return root.next;
    }
};
class BestSolution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return head;
        }
        
        Node* node = head;
        while (node != nullptr) {
            Node* copy = new Node(node -> val, nullptr, nullptr);
            copy -> next = node -> next;
            node -> next = copy;
            node = copy -> next;
        }
        node = head;
        while (node != nullptr) {
            if (node -> random != nullptr) {
                node -> next -> random = node -> random -> next;
            }
            node = node -> next -> next;
        }
        
        node = head;
        Node* new_head = head -> next;
        Node* n = new_head;
        while (node != nullptr) {
            node -> next = node -> next -> next;
            if (n -> next != nullptr) {
                n -> next = n -> next -> next;            
            }            
            node = node -> next;
            n = n -> next;
        }
        return new_head;
    }
};
int main()
{
    return 0;
}