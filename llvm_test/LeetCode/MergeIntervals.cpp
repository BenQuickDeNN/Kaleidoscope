#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return intervals;
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res = {intervals[0]};
        int counter = 0;
        for (int i = 1; i < intervals.size(); i++)
            if (intervals[i][0] > res[counter][1])
            {
                res.push_back(intervals[i]);
                counter++;
            }
            else
            {
                if (intervals[i][0] < res[counter][0])
                    res[counter][0] = intervals[i][0];
                if (intervals[i][1] > res[counter][1])
                    res[counter][1] = intervals[i][1];
            }
        return res;
    }
};