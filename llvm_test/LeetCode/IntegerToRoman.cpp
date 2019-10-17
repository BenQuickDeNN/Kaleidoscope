#include <string>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        if (num < 0)
            return "";
        unsigned int a;
        int tmpNum = num;
        const unsigned int lenNUm = 13;
        unsigned int NUM[lenNUm] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
        string ROMAN[lenNUm] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
        string ret = "";
        for (int i = lenNUm - 1; i >= 0; i--)
        {
            a = tmpNum / NUM[i];
            for (int j = 0; j < a; j++)
                ret += ROMAN[i];
            tmpNum -= a * NUM[i];
        }
        return ret;
    }
};