#include <vector>
#include <cstdio>
#include <climits>
#include <map>

using namespace std;

class Solution {
    int lenNums = 0;
    /**
     * @brief quick sort for solution
     * @param nums array to be sorted
     * @param stdIdx index of start position
     * @param endIdx index of final position
    */
    inline void quickSort(vector<int>& nums, int stdIdx, int endIdx)
    {
        if (stdIdx < endIdx)
        {
            int base = nums[stdIdx];
            int i = stdIdx;
            int j = endIdx;
            while (i < j)
            {
                while (i < j && nums[j] >= base)
                    j--;
                if ( i < j)
                    nums[i++] = nums[j];
                while (i < j && nums[i] <= base)
                    i++;
                if (i < j)
                    nums[j--] = nums[i];
            }
            nums[i] = base;
            quickSort(nums, stdIdx, i - 1);
            quickSort(nums, i + 1, endIdx);
        }
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        lenNums = nums.size();
        vector<vector<int>> ret;
        if (lenNums < 3)
            return ret;
        /* 首先排序 —— 使用快排 */
        quickSort(nums, 0, lenNums - 1);
        /* 拼凑三元组 */
        int num1, num2, num3, tmpInt, minKIdx = lenNums - 1, minKVal = nums[0] + nums[1], minJ = 1;
        map<int, int> numMap;
        int i, j, k;
        for (i = 0; i < lenNums - 2; i++)
        {
            num1 = nums[i];
            if (num1 > 0)
                return ret;
            if (i > 0 && num1 == nums[i - 1])
                continue;
            /* 寻找第2个数字 */
            k = minKIdx;
            j = i + 1;
            tmpInt = num1 + nums[k];
            while (nums[j] + tmpInt < 0 && j < k)
                j++;
            minJ = j;
            for (; j < k; j++)
            {
                num2 = nums[j];
                if (num1 + num2 > 0)
                    return ret;
                if (j > i + 1 && num2 == nums[j - 1])
                    continue;
                /* 寻找第3个数字 */
                for (; k > j; k--)
                {
                    num3 = nums[k];
                    if ((tmpInt = num1 + num2 + num3) < 0)
                        break;
                    if (num3 < 0)
                        return ret;
                    if (k < lenNums - 1 && num3 == nums[k + 1])
                        continue;
                    if (!tmpInt)
                    {
                        vector<int> tmpVec;
                        tmpVec.push_back(num1);
                        tmpVec.push_back(num2);
                        tmpVec.push_back(num3);
                        ret.push_back(tmpVec);
                    }
                }
            }
        }
        return ret;
    }
};

#include <algorithm>

class BestSolution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        if (nums.empty() || nums.back() < 0 || nums.front() > 0)
            return res;
        for (int k = 0; k < nums.size(); k++){
            if (nums[k] > 0)
                break;
            if (k > 0 && nums[k] == nums[k - 1])
                continue;
            int target = 0 - nums[k], i = k + 1, j = nums.size() - 1;
            while (i < j)
            {
                if (nums[i] + nums[j] == target)
                {
                    res.push_back({nums[k], nums[i], nums[j]});
                    while (i < j && nums[i] == nums[i + 1])
                        i++;
                    while (i < j && nums[j] == nums[j - 1])
                    {
                        j--;
                        i++;
                        j--;
                    }
                }
                else if(nums[i] + nums[j] < target)
                    i++;
                else
                    j--;
            }
        }
        return res;
    }
};