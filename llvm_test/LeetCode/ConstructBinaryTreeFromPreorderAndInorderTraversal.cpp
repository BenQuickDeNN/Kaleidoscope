#include <vector>
#include <cstdlib>
#include <map>;

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size()==0||inorder.size()==0)
            return NULL;
        return build(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
    }
    TreeNode* build(vector<int>& preorder,int ps,int pe,vector<int>& inorder,int is,int ie){
        //构建根节点
        TreeNode* root=new TreeNode(preorder[ps]);
        root->left=NULL;
        root->right=NULL;
        
        //在中序序列中寻找根节点
        int i=is;
        while(i<=ie&&preorder[ps]!=inorder[i])
            ++i;
        //i指向中序序列中根节点的位置
        int ll=i-is;//左子树的序列长度
        int rl=ie-i;//右子树的序列长度
        
        //构建左右子树        
        if(ll>0){
            root->left=build(preorder,ps+1,ps+ll,inorder,is,is+ll-1);
        }
        if(rl>0){
            root->right=build(preorder,ps+ll+1,pe,inorder,is+ll+1,ie);
        }
        return root;
        
    }
};

#include <stack>

class IterSolution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()){
            return NULL;
        }
        TreeNode* root,*pre;
        bool mark=0;
        stack<TreeNode*> s;
        int cur1=0,cur2=0,l1=preorder.size(),l2=inorder.size();
        root=new TreeNode(preorder[cur1++]);
        s.push(root);
        pre=root;
        while(cur1<l1){
            while(!s.empty()&&s.top()->val==inorder[cur2]){
                pre=s.top();
                s.pop();
                cur2++;
                mark=1;
            }
            if(mark){
                pre->right=new TreeNode(preorder[cur1++]);
                pre=pre->right;
                s.push(pre);
                mark=0;
            }else{
                pre->left=new TreeNode(preorder[cur1++]);
                pre=pre->left;
                s.push(pre);
            }
        }
        return root;
    }
};