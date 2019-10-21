#include <map>
#include <string>

using namespace std;

map<char, int> KVPair = {
        make_pair('I', 1),
        make_pair('V', 5),
        make_pair('X', 10),
        make_pair('L', 50),
        make_pair('C', 100),
        make_pair('D', 500),
        make_pair('M', 1000)
        };
        
class Solution {
    
public:
    int romanToInt(string s) {
        unsigned int lenS = s.size();
        int ret = 0;
        int maxValue = 0;
        int tmpInt;
        
        for (int i = lenS - 1; i >= 0; i--)
        {
            if ((tmpInt = KVPair[s[i]]) >= maxValue)
            {
                maxValue = tmpInt;
                ret += tmpInt;
            }
            else
                ret -= tmpInt;
        }
        return ret;
    }
};