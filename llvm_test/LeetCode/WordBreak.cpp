#include <string>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        bool dp[s.size() + 1] = {false};
        dp[0] = true;
        for(int i=0; i<=s.size(); ++i) {
            for(auto word: wordDict) {
                int ws = word.size();
                if(i - ws >= 0) {
                    int cur = s.compare(i-ws, ws, word);
                    if (cur==0 && dp[i-ws]==1) {
                        dp[i] = 1;
                    }
                }
            }
        }
        return dp[s.size()];
    }
};