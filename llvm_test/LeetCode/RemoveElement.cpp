#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n;
        if (!(n = nums.size()))
            return 0;
        int* p = &nums[0];
        nums.clear();
        for (int i = 0; i < n; i++)
            if (p[i] != val)
                nums.push_back(p[i]);
        return nums.size();
    }
};