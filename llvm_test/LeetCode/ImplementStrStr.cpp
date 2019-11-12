#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty())
            return 0;
        for (int i = 0; i < haystack.size(); i++)
            if (haystack[i] == needle[0])
                if (needle.size() + i > haystack.size())
                    return -1;
                else if (!haystack.substr(i, needle.size()).compare(needle))
                    return i;
        return -1;
    }
};