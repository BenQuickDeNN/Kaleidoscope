#include <climits>
#include <cmath>

class Solution {
public:
    int divide(int dividend, int divisor) {
        // 特判
        if (divisor == 0)
            return INT_MAX;
        if (divisor == 1)
            return dividend;
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        
        int signdiff = (dividend > 0) ^ (divisor >0);
        
        long t = abs((long)dividend);
        long d = abs((long)divisor);
        int result = 0;
        
        for (int i = 31; i >= 0; i --){
            if ((t >> i) >= d){
                result += 1 << i;
                t -= d << i;
            }
        }
        return signdiff ? -result : result;
    }
};