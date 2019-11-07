#include <cstdlib>

using namespace std;

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode res(0);
        res.next = head;
        ListNode* pp = &res;
        ListNode* pk = pp;
        ListNode* p;
        ListNode* p_old;
        while (pp)
        {
            for (int i = 0; i < k; i++)
                if (!(pk = pk->next))
                    return res.next;
            p_old = pp->next;
            while (pp->next != pk)
            {
                p = pp->next;
                pp->next = p->next;
                p->next = pk->next;
                pk->next = p;
            }
            pp = p_old;
            pk = pp;
        }
        return res.next;
    }
};