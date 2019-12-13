#include <algorithm>

using namespace std;

class Fenshu
{
public:
    unsigned long fenzi;
    unsigned long fenmu;
    Fenshu operator*(const Fenshu& fs)
    {
        Fenshu res(fenzi * fs.fenzi, fenmu * fs.fenmu);
        return res;
    }
    int toInt()
    { return (int)(fenzi / fenmu); }
    float toFloat()
    { return ((float)fenzi) / ((float)fenmu); }
    Fenshu(){}
    Fenshu(const unsigned long& fenzi, const unsigned long& fenmu) :
        fenzi(fenzi), fenmu(fenmu) {}
};
class Solution {
    int C_m_n(const int& m, const int& n)
    {
        Fenshu res(1, 1);
        Fenshu temp;
        for (temp.fenzi = m + 1; temp.fenzi <= n; temp.fenzi++)
        {
            temp.fenmu = temp.fenzi - m;
            res = res * temp;
            /* 约分 */
            for (unsigned long j = 2; j <= res.fenmu; j++)
                while (!(res.fenzi % j) && !(res.fenmu % j))
                {
                    res.fenzi /= j;
                    res.fenmu /= j;
                }
        }
        return res.toInt();
    }
public:
    int climbStairs(int n) {
        int res = 1;
        for (int i = 1; i <= n - i; i++)
            res += C_m_n(max(i, n - i - i), n - i);
        return res;
    }
};

class BestSolution {
public:
    int climbStairs(int n) {
        if (n == 1) return 1;
        int first = 1;
        int second = 2;
        int third;
        for (int i = 3; i <= n; i++)
        {
            third = first + second;
            first = second;
            second = third;
        }
        return second;
    }
};