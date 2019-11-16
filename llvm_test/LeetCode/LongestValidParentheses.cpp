#include <cstdio>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> stackL;
        vector<int> stackR;
        vector<int> stackLR;
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] == ')')
                stackR.push_back(i);
            else
                if (!stackR.empty())
                    stackR.pop_back();
                else
                    stackL.push_back(i);
        while (true)
        {
            if (!stackL.empty() && !stackR.empty())
                if (stackL.back() < stackR.back())
                {
                    stackLR.push_back(stackL.back());
                    stackL.pop_back();
                }
                else
                {
                    stackLR.push_back(stackR.back());
                    stackR.pop_back();
                }
            else if (!stackL.empty())
            {
                stackLR.push_back(stackL.back());
                stackL.pop_back();
            }
            else if (!stackR.empty())
            {
                stackLR.push_back(stackR.back());
                stackR.pop_back();
            }
            else
                break;
        }
        if (stackLR.empty())
            return s.size();
        int res = stackLR[0];
        int tmpInt;
        for (int i = 1; i < stackLR.size(); i++)
            if ((tmpInt = stackLR[i] - stackLR[i - 1] - 1) > res)
                res = tmpInt;
        if ((tmpInt = s.size() - stackLR[stackLR.size() - 1] - 1) > res)
            return tmpInt;
        return res;
    }
};
class BestSolution {
public:
    int longestValidParentheses(string s) {
        int res = 0;
        int len = s.length();
        int *dp = new int[len];
        memset(dp, 0, sizeof(int) * len);
        for(int i = 1; i < len; ++i){
            if(s[i] == ')'){
                if(s[i - 1] == '('){
                    dp[i] = (i > 2 ? dp[i - 2] : 0) + 2;
                }else if(i - dp[i - 1] > 0 && s[i - dp[i -1] - 1] == '('){
                    dp[i] = dp[i - 1] + ((i - dp[i -1] > 2) ? dp[i - dp[i -1] - 2] : 0) + 2;
                }
            } 
            res = max(dp[i], res);
        }
        return res;
    }
};