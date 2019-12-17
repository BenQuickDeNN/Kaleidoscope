#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int leftIdx = -1;
        for (int i = 0; i < nums.size(); i++)
            if (nums[i] > 0)
            {
                leftIdx = i;
                break;
            }
        if (leftIdx < 0)
            return 1;
        else if (nums[leftIdx] > 1)
            return 1;
        else
        {
            int len = 1;
            for (int i = leftIdx + 1; i < nums.size(); i++)
            {
                if (nums[i] > len + 1)
                    return len + 1;
                else if (nums[i] == len + 1)
                    len++;
            }
            return len + 1;
        }
    }
};