#include <cstdlib>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    ListNode* getIntersect(ListNode* head)
    {
        // 使用快慢指针法
        ListNode* slowP = head;
        ListNode* fastP = head;
        // 用快指针追一圈之后追上慢指针或碰到NULL
        while (fastP != NULL && fastP->next != NULL)
        {
            slowP = slowP->next;
            fastP = fastP->next->next;
            if (slowP == fastP)
                return slowP;
        }
        return NULL;
    }
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL)
            return NULL;
        ListNode* intersect = getIntersect(head);
        if (intersect == NULL)
            return NULL;
        ListNode* ptr1 = head;
        ListNode* ptr2 = intersect;
        while (ptr1 != ptr2)
        {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        return ptr1;
    }
};

#include <climits>

class BestSolution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *p =head;
        while(p!=NULL)
        {
            if((p->val^INT_MIN)==0)    
                return p;
            p->val=INT_MIN; 
            p=p->next;
        }
        return NULL;
    }
};