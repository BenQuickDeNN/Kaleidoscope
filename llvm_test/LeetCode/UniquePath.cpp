class Solution {
    int C_m_n(const int& m, const int& n)
    {
        unsigned long long int fenzi = 1;
        unsigned long int fenmu = 1;
        for (unsigned int i = m + 1; i <= n; i++)
            fenzi *= i;
        for (unsigned int i = 2; i <= n - m; i++)
            fenmu *= i;
        return (int)(fenzi / fenmu);
    }
public:
    int uniquePaths(int m, int n) {
        /* 计算路径长度 */
        int u = m + n - 2;
        /* 计算向下或向右的次数，哪个小就用哪个 */
        int v = m < n ? m - 1 : n - 1;
        /* 计算组合数C^{v}_{u} */
        return C_m_n(v, u);
    }
};