
#include <cstdio>
#include <string>

using namespace std;

class Solution
{
public:
    static int lengthOfLongestSubstring_best(string s)
    {
        int  size,i=0,j,k,max=0;
        size = s.size();//母串长度大小
        for(j = 0;j<size;j++)
        {
            for(k = i;k<j;k++)
                if(s[k]==s[j])
                {
                    i = k+1;
                    break;
                }
            if(j-i+1 > max)
                max = j-i+1;
        }
        return max; 
    }

    static int lengthOfLongestSubstring(string s)
    {
        unsigned short strLen = s.size(); // length of substring
        if (!strLen)
            return 0;
        char tmpChar;
        long unsigned int letterMask[2] = {0, 0};    // mask of 26 letters
        long unsigned int tmpMask[2];
        long unsigned int tmpMask2[2];
        const long unsigned int ONE = 1;
        unsigned short sIdx = 0;          // start index of substring
        unsigned short eIdx = 0;          // end index of substring
        unsigned short maxLen = 0;        // max length of substring
        unsigned short substrlen = 0;     // length of substring

        const char Lenlong = 64;     // length of long type (bits)
        unsigned char tmpIdx;
        unsigned char tmpIdx2;

        while (eIdx < strLen)
        {
            tmpChar = s[eIdx];
            tmpIdx = tmpChar / Lenlong;
            tmpMask[tmpIdx] = (ONE << (tmpChar % Lenlong));
            
            if (letterMask[tmpIdx] & tmpMask[tmpIdx])
            {
                // the letter already exist
                substrlen = eIdx - sIdx;
                maxLen = substrlen > maxLen ? substrlen : maxLen;
                while (sIdx <= eIdx)
                {
                    tmpChar = s[sIdx];
                    tmpIdx2 = tmpChar / Lenlong;
                    tmpMask2[tmpIdx2] = (ONE << (tmpChar % Lenlong));
                    if (tmpMask2[tmpIdx2] == tmpMask[tmpIdx])
                    {
                        sIdx++;
                        break;
                    }
                    letterMask[tmpIdx2] &= ~(tmpMask2[tmpIdx2]);
                    sIdx++;
                }
            }
            else
                letterMask[tmpIdx] |= tmpMask[tmpIdx];
            eIdx++;
        }
        /* finishing scanning */
        substrlen = strLen - sIdx;
        maxLen = substrlen > maxLen ? substrlen : maxLen;
        return maxLen;
    }
};

int main()
{
    printf("%d\r\n", Solution::lengthOfLongestSubstring("abcabcbb"));
    printf("%d\r\n", Solution::lengthOfLongestSubstring("bbbbb"));
    printf("%d\r\n", Solution::lengthOfLongestSubstring("pwwkew"));
    printf("%d\r\n", Solution::lengthOfLongestSubstring("   "));
    printf("%d\r\n", Solution::lengthOfLongestSubstring("aabaab!bb"));
}