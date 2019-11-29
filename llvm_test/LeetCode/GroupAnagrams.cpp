#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        if (strs.empty())
            return res;
        bool flag1;
        string tmpStr;
        vector<string> sortedList;
        for (int i = 0; i < strs.size(); i++)
        {
            flag1 = false;
            tmpStr = strs[i];
            sort(tmpStr.begin(), tmpStr.end());
            for (int j = 0; j < sortedList.size(); j++)
                if (sortedList[j] == tmpStr)
                {
                    res[j].push_back(strs[i]);
                    flag1 = true;
                    break;
                }
            if (!flag1)
            {
                vector<string> tmpVec;
                tmpVec.push_back(strs[i]);
                res.push_back(tmpVec);
                string tmpStr2 = strs[i];
                sort(tmpStr2.begin(), tmpStr2.end());
                sortedList.push_back(tmpStr2);
            }
        }
        return res;
    }
};

#include <unordered_map>

class BestSolution {
public:
    using vvs = vector<vector<string>>;
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
      unordered_map<string, vector<string>> hash;
      for (auto &str: strs) {
        auto temp_str = str;
        sort(temp_str.begin(), temp_str.end());
        hash[temp_str].push_back(str);
      }
      vvs res;
      for (auto &it: hash) {
        res.push_back(std::move(it.second));
      }
      return res;
    }
};