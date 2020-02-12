#include <cstdlib>


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if  (head == NULL || head->next == NULL) return head;

        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast->next != NULL) {
            slow = slow->next;
            fast = fast->next;
            if (fast->next != NULL) fast = fast->next;
        }
        fast = slow->next;
        slow->next = NULL;

        fast = sortList(fast);
        slow = sortList(head);

        ListNode h(-1);
        ListNode *tail = &h;
        while (fast != NULL && slow != NULL) {
            if (slow->val  <= fast->val) {
                tail->next = slow;
                slow = slow->next;
            } else {
                tail->next = fast;
                fast = fast->next;
            }
            tail = tail->next;
        }
        tail->next = (slow == NULL) ? fast : slow;
        return h.next;
    }
};