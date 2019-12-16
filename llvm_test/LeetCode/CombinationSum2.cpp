#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        if(candidates.empty())return {};
        sort(candidates.begin(),candidates.end());
        vector<int> track;
        vector<vector<int>> result;
        backtrack(candidates,track,result,0,target);
        return result;
    }
    
    void backtrack(vector<int>& candidates,vector<int> track,vector<vector<int>>& result,int index,int target)
    {
        if(target==0)
            result.push_back(track);
        else{
            for(int i=index;i<candidates.size();++i)
            {
                /*剪枝：连续相同数字会造成重复的组合数组*/
                if(i > index && candidates[i] == candidates[i-1])
                    continue;
                if(target-candidates[i]>=0)
                {
                    track.push_back(candidates[i]);
                    backtrack(candidates,track,result,i+1,target-candidates[i]);
                    track.pop_back();
                }
            }
        }
    }
};

class BestSolution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> path;
        if(candidates.empty())
            return ans;
        sort(candidates.begin(),candidates.end());
        DFS(candidates,0,candidates.size(),path,ans,target);     
        return ans;
    }
 
    void DFS(vector<int>& candidates,int begin,int size,vector<int>& path, vector<vector<int>>& ans,int target)
    {
        if(target==0)//找到了满足条件的  添加到ans中 并终止递归
        {
            ans.push_back(path);
            return;
        }
        int temp;
        for(int i=begin;i<size;++i)
        {
            if(i>begin&&candidates[i]==candidates[i-1])continue;
            temp=target-candidates[i];
            if(temp<0)//递归终止 已经不可能满足条件了 相当于剪枝操作
                break;
            path.push_back(candidates[i]);//走到这边说明还是有可能满足条件的
            DFS(candidates,i+1,size,path,ans,temp);//继续递归操作 
            path.pop_back();//走到这边说明之前压入path的candidates[i]其实是不符合要求的  删去 
            //pop_back的原因：仅考虑本次DFS内部 
            //case1:找到一个answer 直接返回
            //case2:for循环中 不可能有满足条件的 break
            //case3:还有可能找到满足条件的answer 开启下一次的DFS
            //真的走到这一步，只能说明经过candidates[i]的路是不通的  所以要pop_back 相当于回溯到前一个节点 因为如果经过这个节点是行得通的  其就会调用DFS，开启下一次递归 不会走到这个地方来
        }
    }
};