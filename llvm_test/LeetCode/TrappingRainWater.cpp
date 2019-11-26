#include <vector>
#include <cmath>
#include <climits>
#include <cstdio>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        vector<int> HStack; // 存储墙壁高度
        vector<int> IdxStack; // 存储墙壁的位置
        int waterDepth; // 水深
        int minHeight;
        int maxHeight;
        for (int i = 0; i < height.size(); i++)
            if (height[i])
            {
                maxHeight = 0;
                while (!HStack.empty())
                {
                    if (HStack.back() <= maxHeight)
                        break;
                    maxHeight = HStack.back();
                    minHeight = min(HStack.back(), height[i]);
                    waterDepth = INT_MAX;
                    for (int j = IdxStack.back() + 1; j < i; j++)
                        if ((minHeight - height[j]) < waterDepth)
                            waterDepth = minHeight - height[j];
                    if (waterDepth != INT_MAX)
                        res += (i - IdxStack.back() - 1) * waterDepth;
                    if (HStack.back() == height[i])
                    {
                        HStack.pop_back();
                        IdxStack.pop_back();
                        break;
                    }
                    else if (HStack.back() < height[i])
                    {
                        HStack.pop_back();
                        IdxStack.pop_back();
                    }
                }
                HStack.push_back(height[i]);
                IdxStack.push_back(i);
            }
        return res;
    }
};