#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        set<int> num_set;
        set<int>::iterator num_set_it;
        int currentNum;
        int currentStreak;
        for (int num : nums)
            num_set.insert(num);
        int res = 0;
        for (int num : num_set)
        {
            if ((num_set_it = num_set.find(num - 1)) == num_set.end())
            {
                currentNum = num;
                currentStreak = 1;
                while ((num_set_it = num_set.find(currentNum + 1)) != num_set.end())
                {
                    currentNum++;
                    currentStreak++;
                }
                if (currentStreak > res)
                    res = currentStreak;
            }
        }
        return res;
    }
};

#include <unordered_map>

class BestSolution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size()<2)return nums.size();
        int res = 0;
        unordered_map<int,int> hashmap;
        for(int i=0;i<nums.size();++i)
        {
            if(hashmap.count(nums[i])==0)
            {
                int left =0,right =0;
                if(hashmap.count(nums[i]-1)>0)
                {
                    left = hashmap[nums[i]-1];
                }
                if(hashmap.count(nums[i]+1)>0)
                {
                    right = hashmap[nums[i]+1];
                }
                hashmap[nums[i]]=left +right +1;
                if(left!=0)
                {
                    hashmap[nums[i]-left] =left+right+1 ;
                }
                if(right!=0)
                {
                    hashmap[nums[i]+right] =left+right+1 ;
                }
                res= max(res,left+right+1);
            }
        }
        return res;
    }
};