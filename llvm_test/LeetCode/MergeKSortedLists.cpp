#include <cstdlib>
#include <vector>
#include <climits>
#include <cstdio>

using namespace std;

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() <= 1)
            return lists.size() == 1 ? lists[0] : NULL;
        ListNode res(INT_MIN);
        ListNode* p = &res;
        /*
        while (true)
        {
            int tmpIdx = -1;
            int minVal = INT_MAX;
            for (int i = 0; i < lists.size(); i++)
            {
                if (lists[i])
                    if ((*lists[i]).val < minVal)
                    {
                        minVal = (*lists[i]).val;
                        tmpIdx = i;
                    }
            }
            if (tmpIdx != -1)
            {
                (*p).next = lists[tmpIdx];
                lists[tmpIdx] = (*lists[tmpIdx]).next;
                p = (*p).next;
            }
            else
                return res.next;
        }
        */
        (*p).next = lists[0];
        ListNode* tmpP;
        for (int i = 1; i < lists.size(); i++)
        {
            p = &res;
            while (p && lists[i])
            {
                if ((*p).next)
                {
                    if ((*((*p).next)).val > (*lists[i]).val)
                    {
                        //printf("add value %d\r\n", (*lists[i]).val);
                        tmpP = (*p).next;
                        (*p).next = lists[i];
                        lists[i] = (*lists[i]).next;
                        (*((*p).next)).next = tmpP;
                        p = (*p).next;
                    }
                    else
                    {
                        p = (*p).next;
                    }
                }
                else
                {
                    (*p).next = lists[i];
                    break;
                }
            }
        }
        return res.next;
    }
};
class BestSolution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 合并k个有序
        
        
        int n = lists.size();
        if(n <= 1){
            return n == 1 ? lists[0] : nullptr;
        }
        
        return mergeRecursive(lists, 0, n - 1);

    }
    
    ListNode* mergeRecursive(vector<ListNode*>& lists, int l, int r){
        if(l == r){
            return lists[l];
        }
        
        int mid = (l + r) / 2;
        auto left = mergeRecursive(lists, l , mid);
        auto right = mergeRecursive(lists, mid + 1, r);
        return merge2(left, right);
    }
    
    ListNode* merge2(ListNode* a, ListNode* b){
        if(!a || !b){return !a ? b : a;}
        
        
        ListNode* ret;
        ListNode* head = a->val < b->val ? a : b;
        a = head == a ? a->next : a;
        b = head == b ? b->next : b;
        ret = head;
        
        while(a && b){
            if(a->val < b->val){
                ret = ret->next = a;
                a = a->next;
                
            }else{
                ret = ret->next = b;
                b = b->next;
            }
        }
        
        if(a){
            ret->next = a;
        }else if(b){
            ret->next = b;
        }
        
        return head;
    }
    
};
int main()
{
    ListNode node_1_1(1);
    ListNode node_1_2(4);
    ListNode node_1_3(5);
    node_1_2.next = &node_1_3;
    node_1_1.next = &node_1_2;
    ListNode node_2_1(1);
    ListNode node_2_2(3);
    ListNode node_2_3(4);
    node_2_2.next = &node_2_3;
    node_2_1.next = &node_2_2;
    ListNode node_3_1(2);
    ListNode node_3_2(6);
    node_3_1.next = &node_3_2;
    vector<ListNode*> nodes;
    nodes.push_back(&node_1_1);
    nodes.push_back(&node_2_1);
    nodes.push_back(&node_3_1);
    Solution sol;
    ListNode* res = sol.mergeKLists(nodes);
    while (res)
    {
        printf("->%d", (*res).val);
        res = (*res).next;
    }
    printf("\r\n");
    return 0;
}