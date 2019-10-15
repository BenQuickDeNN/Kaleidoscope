#include <climits>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
        int y = 0;
        int i = x;
        int r1;
        while (i > 0)
        {
            if (y > (INT_MAX - (r1 = i % 10)) / 10)
                return false;
            y = y * 10 + r1;
            i /= 10;
        }
        return y == x;
    }
};