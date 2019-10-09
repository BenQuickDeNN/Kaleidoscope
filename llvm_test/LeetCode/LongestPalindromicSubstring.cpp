
#include <cstdio>
#include <string>

using namespace std;

class Solution
{
public:
    static string longestPalindrome(string s) 
    {
        /* 最长回文子串，采用Manacher算法（马拉车算法） */
        const unsigned short lenS = s.size();
        if (!lenS)
            return "";
        /* 填充字符串 */
        string sNew = "^";
        for (int i = 0; i < lenS; i++)
            sNew = sNew + "#" + s[i];
        sNew = sNew + "#$";
        const unsigned short lenSNew = sNew.size();
        /* 计算中心半径 */
        unsigned short P[lenSNew];
        return sNew;
    }
};

int main()
{
    printf("sNew = \"%s\"\r\n", Solution::longestPalindrome("abbvcdad").c_str());
}