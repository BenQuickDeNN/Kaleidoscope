#include <cstdlib>
#include <cmath>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    bool validateBST(const TreeNode* node, const long& minVal, const long& maxVal, const TreeNode* root)
    {
        bool res = true;
        if (node->left != NULL)
            if (node->left->val >= node->val || 
                ((node->left->val <= minVal) && 
                node != root))
                return false;
            else
            {
                long tmpval = (long)(node->val);
                res = res && validateBST(node->left, minVal, tmpval, root);
            }
        if (!res)
            return res;
        if (node->right != NULL)
            if (node->right->val <= node->val || 
                ((node->right->val >= maxVal) && 
                node != root))
                return false;
            else
            {
                long tmpval = (long)(node->val);
                res = res && validateBST(node->right, tmpval, maxVal, root);
            }
        return res;
    }
public:
    bool isValidBST(TreeNode* root) {
        if (root == NULL)
            return true;
        return validateBST(root, LONG_MIN, LONG_MAX, root);
    }
};