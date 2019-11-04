#include <string>
#include <vector>

using namespace std;

class Solution {
    void subProb(vector<string>& res, string str, const int& l, int count, const int& n)
    {
        str[l] = '(';
        if (++count >= n)
            res.push_back(str);
        else
            for (int i = l + 1; i <= 2 * count; i++)
                subProb(res, str, i, count, n);
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string tmpStr(2 * n, ')');
        subProb(res, tmpStr, 0, 0, n);
        return res;
    }
};

int main()
{
    Solution sol;
    vector<string> res = sol.generateParenthesis(3);
    //for (int i = 0; i < res.size(); i++)
    //    printf("%s\r\n", res[i].c_str());
    return 0;
}