#include <cstdlib>
#include <algorithm>

using namespace std;

/*  Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head)
            return head;
        if (!head->next)
            return head;
        ListNode res(0);
        res.next = head;
        ListNode* pp = &res;
        ListNode* pn;
        while (head && (pn = head->next))
        {
            head->next = pn->next;
            pn->next = head;
            pp->next = pn;
            pp = head;
            head = head->next;
        }
        return res.next;
    }
};