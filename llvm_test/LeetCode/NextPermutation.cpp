#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() <= 1)
            return;
        /* 找到一个小于右邻的字符 */
        int tmpInt;
        for (int i = nums.size() - 1; i >= 0; i--)
            if (nums[i] < nums[tmpInt = (i + 1) % nums.size()])
                for (int j = nums.size() - 1; j >= 0; j--) // 从右至左，找到第一个大于nums[idx_1]的字符
                    if (nums[j] > nums[i])
                    {
                        /* 交换两个位置的值 */
                        nums[j] += nums[i];
                        nums[i] = nums[j] - nums[i];
                        nums[j] -= nums[i];
                        /* 对idx1后的数进行排序 */
                        int* p = &nums[tmpInt];
                        sort(p, p + (nums.size() - tmpInt));
                        return;
                    }
    }
};