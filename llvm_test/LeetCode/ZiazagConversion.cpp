#include <cstdio>
#include <string>

using namespace std;

class Solution
{
public:
    static string convert(string s, int numRows) {
        if (numRows == 1) return s;
        unsigned int n = s.size();
        string ret = s;
        unsigned int cycleLen = 2 * numRows - 2;
        unsigned int iDx = 0;
        unsigned int i;
        unsigned int j;
        /* i = 0 */
        for (j = 0; j < n; j += cycleLen) 
            ret[iDx++] = s[j];
        /* 0 < i < cycleLen / 2 */
        for (i = 1; i < cycleLen / 2; i++)
        {
            for (j = cycleLen - i; j < n; j += cycleLen) 
            {
                ret[iDx++] = s[j - cycleLen + 2 * i];
                ret[iDx++] = s[j];
            }
            for(j = j - cycleLen + 2 * i; j < n; j += cycleLen)
                ret[iDx++] = s[j];
        }
        /* cycleLen / 2 <= i < numRows - 1 */
        for (; i < numRows - 1; i++)
            for (j = i; j < n; j += cycleLen) 
            {
                ret[iDx++] = s[j];
                ret[iDx++] = s[j + cycleLen - 2 * i];
            }
        /* i = numRows - 1 */
        for (j = i; j < n; j += cycleLen) 
            ret[iDx++] = s[j];
        return ret;
    }
};

int main()
{
    printf("%s\r\n", Solution::convert("PAYPALISHIRING", 3));
}