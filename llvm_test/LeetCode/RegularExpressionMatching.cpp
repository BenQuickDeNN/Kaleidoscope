#include <string>
#include <cstdlib>

using namespace std;

class Solution {
    unsigned char* memo;
    int lenS;
    int lenP;
    static const unsigned char invalid = 255;
    static const unsigned char TRUE = 1;
    static const unsigned char FALSE = 0;
public:
    bool dp(const int& i, const int& j, const string& s, const string& p)
    {
        unsigned memoIdx = i * (lenP + 1) + j;
        if (memo[memoIdx] != invalid)
            return memo[memoIdx] == TRUE;
        bool ans;
        if (j == lenP)
            ans = i == lenS;
        else
        {
            bool first_match = (i < lenS && (p[j] == s[i] || p[j] == '.'));
            if (j + 1 < lenP && p[j + 1] == '*')
                ans = (dp(i, j + 2, s, p) || first_match && dp(i + 1, j, s, p));
            else
                ans = first_match && dp(i + 1, j + 1, s, p);
        }
        if (ans)
            memo[memoIdx] = TRUE;
        else
            memo[memoIdx] = FALSE;
        return ans;
    }
    bool isMatch(string s, string p) 
    {
        lenS = s.size();
        lenP = p.size();
        memo = (unsigned char*)malloc((lenS + 1) * (lenP + 1) * sizeof(unsigned char));
        for (int i = 0; i < (lenS + 1) * (lenP + 1); i++)
            memo[i] = invalid;
        return dp(0, 0, s, p);
    }
};