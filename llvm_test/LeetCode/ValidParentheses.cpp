#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        vector<char> stack;
        for (int i = 0; i < s.size(); i++)
            if (s[i] == ')')
                if (stack.empty())
                    return false;
                else if (stack.back() != '(')
                    return false;
                else
                    stack.pop_back();
            else if (s[i] == ']')
                if (stack.empty())
                    return false;
                else if (stack.back() != '[')
                    return false;
                else
                    stack.pop_back();
            else if (s[i] == '}')
                if (stack.empty())
                    return false;
                else if (stack.back() != '{')
                    return false;
                else
                    stack.pop_back();
            else
                stack.push_back(s[i]);
        return stack.empty();
    }
};