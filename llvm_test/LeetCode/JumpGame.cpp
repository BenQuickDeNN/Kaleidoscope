#include <vector>

using namespace std;

class Solution {
    bool testJJump(const vector<int>& nums, const int& idx, const int& istart)
    {
        if (idx >= nums.size() - 1)
            return true;
        if (!nums[idx])
            return false;
        int i = idx + nums[idx];
        bool res = false;
        while (i > istart)
        {
            if ((res = testJJump(nums, i, idx + nums[idx])))
                break;
            --i;
        }
        return res;
    }
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty())
            return false;
        else
            return testJJump(nums, 0, 0);
    }
};

class BestSolution {
public:
    bool canJump(vector<int>& nums) 
    {
        int k = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > k) return false;
            k = max(k, i + nums[i]);
        }
        return true;
    }
};