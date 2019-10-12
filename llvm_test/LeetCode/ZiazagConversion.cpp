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
        unsigned int k;
        /* i = 0 */
        for (j = 0; j < n; j += cycleLen) 
            ret[iDx++] = s[j];
        /* 0 < i < numRows - 1 */
        for (i = 1; i < numRows - 1; i++)
        {
            for (j = i, k = cycleLen - i; j < n && k < n; j += cycleLen, k += cycleLen) 
            {
                ret[iDx++] = s[j];
                ret[iDx++] = s[k];
            }
            for(; j < n; j += cycleLen)
                ret[iDx++] = s[j];
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