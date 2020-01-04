#include <cstdlib>
#include <queue>

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
   bool isSymmetric(TreeNode* root) {
       return func(root,root);
    }

   bool func(TreeNode* a,TreeNode* b){
       if(!a&&!b)
        return true;
        if(!a||!b)
        return false;
        if(a->val!=b->val)
            return false;
        return func(a->left,b->right)&&func(a->right,b->left);
   }
};