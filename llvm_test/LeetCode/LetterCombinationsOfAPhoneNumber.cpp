#include <string>
#include <vector>

using namespace std;

const string letters[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        if (digits.size() == 0)
            return ret;
        /* 分配首字母 */
        for (int i = 0; i < letters[digits[0] - '0' - 2].size(); i++)
            ret.push_back(letters[digits[0] - '0' - 2][i] + "");
        for (int i = 1; i < digits.size(); i++)
        {
            for (int j = 0; j < letters[digits[i] - '0' - 2].size(); j++)
        }
        return ret;
    }
};