#include <algorithm>
#include <vector>
#include <cstdio>
#include <climits>
#include <map>
#include <cmath>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int tar) {
        int ret = 0;
        if (nums.empty())
            return ret;
        if (nums.size() < 3)
            return ret;
        sort(nums.begin(), nums.end());
        printf("[");
        for (int i = 0; i < nums.size(); i++)
            printf("%d, ", nums[i]);
        printf("]\r\n");
        int minDistance = INT32_MAX;
        int tmpInt;
        for (int k = 0; k < nums.size(); k++){
            if (k > 0 && nums[k] == nums[k - 1])
                continue;
            int target = tar - nums[k], i = k + 1, j = nums.size() - 1;
            while (i < j)
            {
                if ((tmpInt = abs(target - (nums[i] + nums[j]))) < minDistance)
                {
                    minDistance = tmpInt;
                    ret = nums[k] + nums[i] + nums[j];
                    printf("[%d, %d, %d], sum = %d, k = %d, i = %d, j = %d\r\n", nums[k], nums[i], nums[j], ret, k, i, j);
                    while (i < j && nums[j] == nums[j - 1])
                        j--;
                }
                else if(nums[i] + nums[j] < target)
                    i++;
                else
                    j--;
            }
        }
        return ret;
    }
};

class BestSolution {
public:
    //双指针法，先排序，再双指针。
    int threeSumClosest(vector<int>& nums, int target) {
        int ret =nums[0]+nums[1]+nums[2];
        int size=nums.size()-2;
        sort(nums.begin(),nums.end());
        if(size==1)return ret;
        for(int i=0;i<size;++i)
        {
            int right=size+1;
            int left=i+1;
            int tempval=target-nums[i];
            int twosum;
            int pregap=abs(target-nums[i]-nums[left]-nums[right]);
            int presum,nowsum,nowgap;
            while(left<right)
            {   
                twosum=nums[left]+nums[right];
                if(twosum==tempval)return target;
                nowsum=twosum+nums[i];
                nowgap=abs(target-nowsum);
                if(nowgap>pregap)
                {
                    nowgap=pregap;
                    nowsum=presum;
                }
                if(twosum<tempval)++left;
                else --right;
                presum=nowsum;
                pregap=nowgap;
                    
            }
            ret=nowgap<abs(target-ret)?nowsum:ret;
        }
        return ret;
    }
};

int main()
{
    Solution sol;
    vector<int> tmpParam = {13,2,0,-14,-20,19,8,-5,-13,-3,20,15,20,5,13,14,-17,-7,12,-6,0,20,-19,-1,-15,-2,8,-2,-9,13,0,-3,-18,-9,-9,-19,17,-14,-19,-4,-16,2,0,9,5,-7,-4,20,18,9,0,12,-1,10,-17,-11,16,-13,-14,-3,0,2,-18,2,8,20,-15,3,-13,-12,-2,-19,11,11,-10,1,1,-10,-2,12,0,17,-19,-7,8,-19,-17,5,-5,-10,8,0,-12,4,19,2,0,12,14,-9,15,7,0,-16,-5,16,-12,0,2,-16,14,18,12,13,5,0,5,6};
    sol.threeSumClosest(tmpParam, -59);
    return 0;
}