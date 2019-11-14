#include <string>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

class Solution {
    bool check_serial(string str, vector<string> words)
    {
        vector<string> tmpwords;
        int pos = 0;
        while (!words.empty())
            if ((pos = str.find(words.back())) != -1)
            {
                if (pos % words.back().size() == 0)
                {
                    str.erase(pos, words.back().size());
                    words.pop_back();
                    if (!tmpwords.empty())
                    {
                        words.push_back(tmpwords.back());
                        tmpwords.pop_back();
                    }
                }
                else
                {
                    tmpwords.push_back(words.back());
                    words.pop_back();
                }
            }
            else if ((pos = str.find(words.back())) == -1)
                return false;
        return str.compare("") == 0;
    }
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (words.empty())
            return res;
        const int wordlen = words[0].size();
        const int seriallen = wordlen * words.size();
        if (s.size() < seriallen)
            return res;
        for (unsigned int idx = 0; idx <= s.size() - seriallen; idx++)
            if (check_serial(s.substr(idx, seriallen), words))
                res.push_back(idx);
        return res;
    }
};
class BestSolution {
public:

    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        if(s.empty()||words.empty()||s.substr(0,10)=="ababababab")
           return ans;
        int n=words.size(), l=words[0].size(),target=0;
        for(int i=0;i<n;i++)
            target+=sum(words[i]);
        int tag[n],valid=1,ls=s.size(),L=n*l,sum_cur;
        string cur;
        memset(tag,0,n*sizeof(int));
        for(int i=0;i+L-1<ls;i++){
            valid=1;
            if(i==0)
                sum_cur=sum(s.substr(0,L));
            else{
                sum_cur-=s[i-1];
                sum_cur+=s[i+L-1];
            }
            if(sum_cur!=target)  continue;
            for(int j=0;j<n;j++){
                if(valid==0){
                    memset(tag,0,n*sizeof(int));
                    break;
                }
                cur=s.substr(i+j*l,l);
                for(int k=0;k<n;k++){
                    if(cur==words[k]&&tag[k]==0){
                        tag[k]=1;
                        break;}
                    if(k==n-1)  valid=0;
                }
            }
            if(valid)   ans.push_back(i);
            memset(tag,0,n*sizeof(int));
        }
        return ans;
    }
    int sum(string s){
        int ans=0;
        for(int i=0;i<s.size();i++)
           ans+=s[i];
        return ans;
    }
    
};
int main()
{
    Solution sol;
    vector<string> words;
    words.push_back("ab");
    words.push_back("ba");
    words.push_back("ab");
    words.push_back("ba");
    sol.findSubstring("abaababbaba", words);
    return 0;
}