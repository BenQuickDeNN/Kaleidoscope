/*****************************************************************************************************
* Given an array of integers, return indices of the two numbers such that they add up to a specific 
* target.

* You may assume that each input would have exactly one solution, and you may not use the same
* element twice.

* Example:
* ----------------------------------------
* Given nums = [2, 7, 11, 15], target = 9,

* Because nums[0] + nums[1] = 2 + 7 = 9,
* return [0, 1].
* ---------------------------------------

* Algorithm -- 一遍哈希表
* 在进行迭代并将元素插入到表中的同时，我们还会回过头来检查表中是否已经存在当前元素所对应的目标元素。如果它存在，那我们已
* 经找到了对应解，并立即将其返回。

* 作者：LeetCode
* 链接：https://leetcode-cn.com/problems/two-sum/solution/liang-shu-zhi-he-by-leetcode/
* 来源：力扣（LeetCode）
* 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*****************************************************************************************************/

#include <string>
#include <map>
#include <vector>

class Solution
{
public:
    static std::vector<int> twoSum(std::vector<int>& nums, int target) 
    {
        std::map<int, int> map_num;
        int len_nums = nums.size();
        for (int i = 0; i < len_nums; i++)
        {
            int complement = target - nums[i];
            if (map_num.find(complement) != map_num.end())
            {
                // element exist
                int comIdx = map_num[complement];
                if (comIdx != i)
                {
                    std::vector<int> result { comIdx, i };
                    return result;
                }
            }
            map_num.insert(std::make_pair(nums[i], i));
        }
        fprintf(stderr, "No two sum solution\r\n");
        std::vector<int> result;
        return result;
    }
};

int main()
{
    std::vector<int> nums {2, 7, 11, 15};
    int target = 9;
    std::vector<int> result = Solution::twoSum(nums, target);
    int len = result.size() - 1;
    printf("[");
    for (int i = 0; i < len; i++)
            printf("%d, ", result[i]);
    printf("%d]\r\n", result[len]);
}