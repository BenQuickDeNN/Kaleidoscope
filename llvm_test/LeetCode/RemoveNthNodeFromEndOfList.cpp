#include <cstdlib>

using namespace std;
/*
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode root(0);
        root.next = head;
        ListNode* p = &root;
        for (int i = 0; i < n && head != NULL; i++)
            head = (*head).next;
        while (head != NULL)
        {
            head = (*head).next;
            p = (*p).next;
        }
        if ((*p).next != NULL)
        {
            (*p).next = (*((*p).next)).next;
        }
        else
            return NULL;
        return root.next;
    }
};