#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        if (prices.empty())
            return res;
        const int sz = prices.size();
        int minVal = prices[0];
        for (int i = 1; i < sz; ++i)
        {
            minVal = min(minVal, prices[i]);
            res = max(res, prices[i] - minVal);
        }
        return res;
    }
};