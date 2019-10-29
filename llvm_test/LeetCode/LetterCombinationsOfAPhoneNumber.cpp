#include <string>
#include <vector>

using namespace std;

const string letters[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
inline string getLetterStr(const char& digit)
{
    return letters[digit - '0' - 2];
}
inline char getLetter(const char& digit, const int& idx)
{
    return letters[digit - '0' - 2][idx];
}
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        const int lenDigits = digits.size();
        if (lenDigits == 0)
            return res;
        /* 计算结果所需空间 */
        int lenRes = 1;
        int tmpInts[lenDigits];
        for (int i = lenDigits - 1; i >= 0; i--)
        {
            tmpInts[i] = lenRes;
            lenRes *= getLetterStr(digits[i]).size();
        }
        /* 设置字符串内容 */
        for (int i = 0; i < lenRes; i++)
        {
            string tmpStr(lenDigits, '@');
            res.push_back(tmpStr);
            for (int j = 0; j < lenDigits; j++)
                res[i][j] = getLetter(digits[j], ((i / tmpInts[j]) % getLetterStr(digits[j]).size()));
        }
        return res;
    }
};