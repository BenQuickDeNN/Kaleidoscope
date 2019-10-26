#include <vector>

using namespace std;

class Solution {
    vector<int> swap(vector<int>& nums, const int& idx1, const int& idx2)
    {
        nums[idx1] += nums[idx2];
        nums[idx2] = nums[idx1] - nums[idx2];
        nums[idx1] -= nums[idx2];
        return nums;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        int tmpLen = 1;
        const int lenNums = nums.size();
        for (int i = 2; i <= lenNums; i++)
            tmpLen *= i;
        res.push_back(nums);
        for (int i = 1; i < tmpLen; i++)
            res.push_back(swap(nums, (i - 1) % lenNums, i % lenNums));
        return res;
    }
};