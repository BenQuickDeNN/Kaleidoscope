#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN;
        int tmpSum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (tmpSum > 0)
                tmpSum += nums[i];
            else
                tmpSum = nums[i];
            res = max(res, tmpSum);
        }
        return res;
    }
};