#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

class Solution {
public:
    void helper(vector<int>& candidates, vector<vector<int>>& result, vector<int>& tmp, int k, int target) {
        if (target == 0 ) {
            result.push_back(tmp);
        }
        
        for (int i=k; i<candidates.size(); i++) {
            if (candidates[i] <= target) {
                tmp.push_back(candidates[i]);
                helper(candidates, result, tmp, i, target-candidates[i]);
                tmp.pop_back();
            }
        }
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int len = candidates.size();
        if (len == 0) {
            return {{}};
        }
        
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> tmp;
        
        helper(candidates, result, tmp, 0, target);
        return result;
    }
};