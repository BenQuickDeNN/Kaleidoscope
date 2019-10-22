#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ret = "";
        int vecSize = strs.size();
        if (vecSize == 0)
            return ret;
        int len = strs[0].size();
        int tmpInt;
        for (int i = 1; i < vecSize; i++)
            if ((tmpInt = strs[i].size()) < len)
                len = tmpInt;
        char tmpChar;
        for (int i = 0; i < len; i++)
        {
            tmpChar = strs[0][i];
            for (int j = 1; j < vecSize; j++)
                if (strs[j][i] != tmpChar)
                    return ret;
            ret = ret + tmpChar;
        }
        return ret;
    }
};