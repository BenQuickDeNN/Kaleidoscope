#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int res;
        for (res = 0; res < nums.size() && nums[res] < target; res++)
        {}
        return res;
    }
};
class BestSolution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size(), l = 0, r = n - 1, m;
        while (l < r) {
            m = (l + r) >> 1;
            if (nums[m] == target)
                return m;
            else if (nums[m] < target)
                l = m + 1;
            else
                r = m;
        }
        return nums.back() < target ? n : l;
    }
};