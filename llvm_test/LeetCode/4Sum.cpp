#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        printf("[");
        for (int i = 0; i < nums.size(); i++)
            printf("%d,", nums[i]);
        printf("]\r\n");
        vector<vector<int>> res;
        if (nums.empty() || nums.back() < 0 || nums.front() > 0)
            return res;
        for (int k = 0; k < nums.size(); k++)
        {
            //if (nums[k] > target)
            //    break;
            if (k > 0 && nums[k] == nums[k - 1])
                continue;
            for (int m = k + 1; m < nums.size(); m++)
            {
                //if (nums[k] + nums[m] > target)
                //    break;
                if (m > k + 1 && nums[m] == nums[m - 1])
                    continue;
                int tar = target - nums[k] - nums[m], i = m + 1, j = nums.size() - 1;
                while (i < j)
                {
                    //printf("k=%d, m=%d, i=%d, j=%d\r\n", k, m, i, j);
                    if (nums[i] + nums[j] == tar)
                    {
                        printf("k=%d, m=%d, i=%d, j=%d\r\n", k, m, i, j);
                        printf("nums[k]=%d, nums[m]=%d, nums[i]=%d, nums[j]=%d\r\n", nums[k], nums[m], nums[i], nums[j]);
                        res.push_back({nums[k], nums[m], nums[i], nums[j]});
                        if (i < j)
                            i++;
                        while (i < j && nums[i] == nums[i - 1])
                            i++;
                        //while (i < j && nums[i] == nums[i + 1])
                        //    i++;
                        if (j < nums.size() - 1)
                            while (i < j && nums[j] == nums[j + 1])
                            {
                                j--;
                                i++;
                                j--;
                            }
                        printf("k=%d, m=%d, i=%d, j=%d\r\n", k, m, i, j);
                    }
                    else if(nums[i] + nums[j] < tar)
                        i++;
                    else
                        j--;
                }
            }
        }
        return res;
    }
};

class BestSolution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int n=nums.size();
        if(n<4) return result;
        sort(nums.begin(),nums.end());
        for(int i=0;i<n-3;i++)
        {
            if((nums[i]+nums[i+1]+nums[i+2]+nums[i+3])>target) return result;
            if(i>0&&nums[i-1]==nums[i]) continue;
            if((nums[i]+nums[n-3]+nums[n-2]+nums[n-1])<target) continue;
            for(int j=i+1;j<n-2;j++)
            {
                if((nums[i]+nums[j]+nums[j+1]+nums[j+2])>target) break;
                if(j>i+1&&nums[j-1]==nums[j]) continue;
                if((nums[i]+nums[j]+nums[n-2]+nums[n-1])<target) continue;
                int l=j+1,r=n-1;
                while(l<r)
                {
                    int sum=nums[i]+nums[j]+nums[l]+nums[r];
                    if(sum>target) r--;
                    else if(sum<target) l++;
                    else
                    {
                        vector<int> a;
                        a.push_back(nums[i]);
                        a.push_back(nums[j]);
                        a.push_back(nums[l]);
                        a.push_back(nums[r]);
                        result.push_back(a);
                        while(nums[l]==nums[l+1]&&l+1<r)  l++;
                        while(nums[r]==nums[r-1]&&l<r-1)  r--;
                        l++;
                        r--;
                    }

                }
            }
        }
        return result;
    }
};

int main()
{
    Solution sol;
    vector<int> tmpParam = {-5,-2,-4,-2,-5,-4,0,0};
    sol.fourSum(tmpParam, -13);
    return 0;
}