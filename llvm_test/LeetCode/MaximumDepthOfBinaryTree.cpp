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
    int getDepth(TreeNode* node)
    {
        if (node == NULL)
            return 0;
        else
            return 1 + max(getDepth(node->left), getDepth(node->right));
    }
public:
    int maxDepth(TreeNode* root) {
        return getDepth(root);
    }
};