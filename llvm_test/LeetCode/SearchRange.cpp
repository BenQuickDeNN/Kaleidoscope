#include <vector>
#include <cstdio>

using namespace std;

class Solution {
    int findTarget(const vector<int>& nums, const int& target)
    {
        int LB = 0;
        int RB = nums.size() - 1;
        if (nums[LB] == target)
            return LB;
        else if (nums[RB] == target)
            return RB;
        int res = (LB + RB) / 2;
        int old_res = -1;
        while (nums[res] != target)
        {
            if (res == old_res || LB == RB)
                return -1;
            old_res = res;
            if (nums[res] < target)
            {
                LB = res;
                res = (res + RB) / 2;
            }
            else
            {
                RB = res;
                res = (res + LB) / 2;
            }
            if (res < LB || res > RB)
                return -1;
        }
        return res;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        if (nums.empty())
        {
            res.push_back(-1);
            res.push_back(-1);
            return res;
        }
        int start = -1;
        int end = -1;
        int idx = -1;
        /* find target */
        if ((idx = findTarget(nums, target)) != -1)
        {
            /* find start */
            for (start = idx; start > 0; start--)
                if (nums[start - 1] < target)
                    break;
            /* find end */
            for (end = idx; end  < nums.size() - 1; end++)
                if (nums[end + 1] > target)
                    break;
        }
        res.push_back(start);
        res.push_back(end);
        return res;
    }
};