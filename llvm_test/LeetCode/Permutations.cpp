#include <vector>

using namespace std;

class Solution {
    template<class T> void copy_vector(const vector<T>& source, vector<T>& target)
    {
        for (int i = 0; i < source.size(); i++)
            target.push_back(source[i]);
    }
    template<class T> bool checkExist(const vector<T>& vec, const T& element)
    {
        for (int i = 0; i < vec.size(); i++)
            if (vec[i] == element)
                return true;
        return false;
    }
    void findPermutation(vector<int>& PStack, vector<vector<int>>& res, const vector<int>& nums)
    {
        if (PStack.size() == nums.size())
        {
            vector<int> TStack;
            copy_vector(PStack, TStack);
            res.push_back(TStack);
        }
        else
            for (int i = 0; i < nums.size(); i++)
                if (!checkExist(PStack, nums[i]))
                {
                    PStack.push_back(nums[i]);
                    findPermutation(PStack, res, nums);
                }
        if (!PStack.empty())
            PStack.pop_back();
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty())
            return res;
        /* 使用搜索树 */
        vector<int> PStack;
        findPermutation(PStack, res, nums);
        return res;
    }
};

#include <algorithm>

class BestSolution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> vvRet;
        sort(nums.begin(), nums.end());

        vvRet.push_back(nums);
        while(next_permutation(nums.begin(), nums.end()))
        {
            vvRet.push_back(nums);
        }

        return vvRet;
    }
};