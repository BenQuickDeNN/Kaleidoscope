#include <string>
#include <cctype>
#include <climits>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        int ret = 0;
        unsigned int len = str.size();
        unsigned int i = 0;
        unsigned int endIdx;
        while (str[i] == ' ')
            i++;
        if (str[i] == '-')
        {
            i++;
            if (str[i] == '0')
                while (str[i] == '0')
                    i++;
            endIdx = i + 9;
            endIdx = endIdx < len ? endIdx : len;
            for (; i < endIdx; i++)
            {
                if (!isdigit(str[i]))
                    return ret;
                ret = ret * 10 - (str[i] - '0');
            }
            if (i >= len)
                return ret;
            if (!isdigit(str[i]))
                    return ret;
            if (ret < (INT32_MIN + (str[i] - '0')) / 10)
                return INT32_MIN;
            ret = ret * 10 - (str[i] - '0');
            i++;
            if (i < len)
                if (isdigit(str[i]))
                    return INT32_MIN;
        }
        else if (str[i] == '+')
        {
            i++;
            if (str[i] == '0')
                while (str[i] == '0')
                    i++;
            endIdx = i + 9;
            endIdx = endIdx < len ? endIdx : len;
            for (; i < endIdx; i++)
            {
                if (!isdigit(str[i]))
                    return ret;
                ret = ret * 10 + (str[i] - '0');
            }
            if (i >= len)
                return ret;
            if (!isdigit(str[i]))
                    return ret;
            if (ret > (INT32_MAX - (str[i] - '0')) / 10)
                return INT32_MAX;
            ret = ret * 10 + (str[i] - '0');
            i++;
            if (i < len)
                if (isdigit(str[i]))
                    return INT32_MAX;
        }
        else if (isdigit(str[i]))
        {
            if (str[i] == '0')
                while (str[i] == '0')
                    i++;
            endIdx = i + 9;
            endIdx = endIdx < len ? endIdx : len;
            for (; i < endIdx; i++)
            {
                if (!isdigit(str[i]))
                    return ret;
                ret = ret * 10 + (str[i] - '0');
            }
            if (i >= len)
                return ret;
            if (!isdigit(str[i]))
                    return ret;
            if (ret > (INT32_MAX - (str[i] - '0')) / 10)
                    return INT32_MAX;
            ret = ret * 10 + (str[i] - '0');
            i++;
            if (i < len)
                if (isdigit(str[i]))
                    return INT32_MAX;
        }
        return ret;
    }
};