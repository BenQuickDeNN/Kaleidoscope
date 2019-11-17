#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
	int left = 0;
	int right = nums.size() - 1;

	int mid = left + (right - left)/2;
	while (left <= right)
	{
		if (nums[mid] == target)
			return mid;
		if (nums[left] <= nums[mid])//left must be ascending
		{
			if (nums[left] <= target && target < nums[mid])
				right = mid - 1;
			else
				left = mid + 1;
		}
		else// right must be ascending
		{
			if (nums[mid] < target && target <= nums[right])
				left = mid + 1;
			else
				right = mid - 1;
		}
		mid = left + (right - left) / 2;
	}
	return -1;
    }
};