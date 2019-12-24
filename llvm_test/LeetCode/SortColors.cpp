#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int count0 = 0;
        int count1 = 0;
        const int n = nums.size();
        int i;
        for (i = 0; i < n; i++)
            if (nums[i] == 0)
                count0++;
            else if (nums[i] == 1)
                count1++;
        count1 += count0;
        for (i = 0; i < count0; i++)
            nums[i] = 0;
        for (; i < count1; i++)
            nums[i] = 1;
        for (; i < n; i++)
            nums[i] = 2;
    }
};

#include <algorithm>

class BestSolution {
public:
    void sortColors(vector<int>& nums) {
        int begin = 0;
        int end = nums.size() - 1;

        int i = 0;
        while(i <= end){
            if(nums[i] == 2){
                swap(nums[i], nums[end]);
                end--;
            }else{
                if(nums[i] == 0){
                    swap(nums[begin], nums[i]);
                    begin++;
                }
                i++;
            }
        }
    }
};