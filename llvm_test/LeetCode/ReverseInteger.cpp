#include <climits>

class Solution {
public:
    inline int reverse(int x) {
        register int rev = 0;
        register int pop;
        while (x != 0) 
        {
            pop = x % 10;
            x /= 10;
            if (rev > INT_MAX/10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
            if (rev < INT_MIN/10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
            rev = rev * 10 + pop;
        }
        return rev;
    }
};