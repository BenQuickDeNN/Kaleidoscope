#include <vector>

using namespace std;

class Solution {
    void treeScan(vector<int>* idxStack, vector<vector<int>>* res, const vector<int>& nums)
    {
        vector<int> tmpSet;
        for (int i = 0; i < idxStack->size(); i++)
            tmpSet.push_back(nums[(*idxStack)[i]]);
        res->push_back(tmpSet);
        for (int i = idxStack->back() + 1; i < nums.size(); i++)
        {
            int tmpIdx = i;
            idxStack->push_back(tmpIdx);
            treeScan(idxStack, res, nums);
        }
        if (!idxStack->empty())
            idxStack->pop_back();
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> emptySet;
        res.push_back(emptySet);
        vector<int> idxStack;
        for (int root = 0; root < nums.size(); root++)
        {
            idxStack = {root};
            treeScan(&idxStack, &res, nums);
        }
        return res;
    }
};