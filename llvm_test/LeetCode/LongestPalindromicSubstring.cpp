
#include <cmath>
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
        //string sNew = "^";
        const unsigned short lenSNew = 2 * lenS + 3;
        char sNew[lenSNew];
        sNew[0] = '^';
        for (unsigned short i = 0; i < lenS; i++)
        {
            sNew[2 * i + 1] = '#';
            sNew[2 * i + 2] = s[i];
        }
        sNew[lenSNew - 2] = '#';
        sNew[lenSNew - 1] = '$';
        //printf("sNew = %s\r\n", sNew);
        
        /* 计算中心半径 */
        unsigned short P[lenSNew];
        unsigned short C = 0; // 中心下标
        unsigned short R = 0; // 当前中心的右边界下标
        unsigned short tmpShort;
        for (unsigned short i = 1; i < lenSNew - 1; i++)
        {
            /* 对称法求P[i]，注意防止P[i]的值大于右边界 */
            /* R > i 的情况 */
            if (R > i)
                P[i] = min((unsigned short)(R - i), P[2 * C - i]);
            /* 其他情况 */
            else
                P[i] = 0;
            /* 遇到 P[i]>R、P[i_mirror]遇到了原字符串的左边界、i=R 的情况
            要采用中心扩展法求P[i] */
            while (sNew[i + 1 + P[i]] == sNew[i - 1 - P[i]])
                P[i]++;
            //printf("C = %d, R = %d, P[%d] = %d\r\n", C, R, i, P[i]);
            /* 更新C、R */
            if ((tmpShort = i + P[i]) > R)
            {
                C = i;
                R = tmpShort;
            }
        }
        /* 找出P的最大值，找出最长回文子串 */
        R = 0;
        for (unsigned short i = 1; i < lenSNew - 1; i++)
            if (P[i] > R)
            {
                R = P[i];
                C = i;
            }
        return s.substr((C - R) / 2, R);
    }
};

int main()
{
    printf("%s\r\n", Solution::longestPalindrome("babad").c_str());
    printf("%s\r\n", Solution::longestPalindrome("cbbd").c_str());
}