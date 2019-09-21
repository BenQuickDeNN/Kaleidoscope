/*****************************************************************************************************
* 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储
* 一位 数字。

* 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

* 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

* 示例：
* ----------------------------------------
* 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
* 输出：7 -> 0 -> 8
* 原因：342 + 465 = 807
* ---------------------------------------

* Algorithm:
* 就像你在纸上计算两个数字的和那样，我们首先从最低有效位也就是列表 l1l1l1 和 l2l2l2 的表头开始相加。由于每位数字都应当
* 处于 0…90 \ldots 90…9 的范围内，我们计算两个数字的和时可能会出现 “溢出”。例如，5+7=125 + 7 = 125+7=12。在这种情
* 况下，我们会将当前位的数值设置为 222，并将进位 carry=1carry = 1carry=1 带入下一次迭代。进位 carrycarrycarry 必
* 定是 000 或 111，这是因为两个数字相加（考虑到进位）可能出现的最大和为 9+9+1=199 + 9 + 1 = 199+9+1=19。

* 作者：LeetCode
* 链接：https://leetcode-cn.com/problems/add-two-numbers/solution/liang-shu-xiang-jia-by-leetcode/
* 来源：力扣（LeetCode）
* 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*****************************************************************************************************/

#include <cstdio>

/// Definition for singly-linked list.
struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
    static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        if (l1 != NULL && l2 == NULL)
            return l1;
        else if (l1 == NULL && l2 != NULL)
            return l2;
        else if (l1 == NULL && l2 == NULL)
            return NULL;

        bool carry = false;
        bool flag_l1_end = false;
        bool flag_l2_end = false;
        ListNode *l1_sIdx = l1; // recording the address of l1
        while (true)
        {
            if (carry)  // flag_l1_end must be false
            {
                if (!flag_l2_end)
                    l1->val += l2->val + 1;
                else
                    l1->val++;
            }
            else
            {
                if (!flag_l1_end && !flag_l2_end)
                    l1->val += l2->val;
                else if (flag_l1_end && !flag_l2_end)
                    l1->next = l2;
            }
            if (l1->val < 10)
                carry = false;
            else
            {
                l1->val %= 10;
                // carry
                carry = true;
                if (l1->next == NULL)
                    l1->next = new ListNode(0);
            }
            if (l1->next == NULL && l2->next == NULL)
                break;
            if (l1->next != NULL)
                l1 = l1->next;
            else
                flag_l1_end = true;
            if (l2->next != NULL)
                l2 = l2->next;
            else
                flag_l2_end = true;
        }

        return l1_sIdx;
    }
};

int main()
{
    ListNode *p_l1 = new ListNode(0);
    ListNode *p_l2 = new ListNode(7);

    //p_l1->next = new ListNode(9);
    //p_l1->next->next = new ListNode(9);

    p_l2->next = new ListNode(3);
    //p_l2->next->next = new ListNode(4);

    ListNode *result = Solution::addTwoNumbers(p_l1, p_l2);

    while (true)
    {
        printf("%d, ", result->val);
        if (result->next != NULL)
            result = result->next;
        else
            break;
    } 
    printf("\r\n");
}