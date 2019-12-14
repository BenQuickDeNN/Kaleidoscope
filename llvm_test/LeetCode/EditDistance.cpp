#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2)
    {
        const int I = word1.size() + 1;
        const int J = word2.size() + 1;
        /* 初始化编辑距离 */
        int D[I][J];
        int i, j;
        for (i = 0; i < I; i++)
            D[i][0] = i;
        for (j = 1; j < J; j++)
            D[0][j] = j;
        /* 遍历 */
        for (i = 1; i < I; i++)
            for (j = 1; j < J; j++)
                if (word1[i - 1] == word2[j - 1])
                    D[i][j] = D[i - 1][j - 1]; // 直接插入前面的字符串
                else
                    D[i][j] = 1 + min(D[i - 1][j], min(D[i][j - 1], D[i - 1][j - 1]));
        return D[I - 1][J - 1];
    }
};