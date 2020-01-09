#include <cstdlib>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    void expand(TreeNode* node)
    {
        if (node == NULL)
            return;
        if (node->left != NULL)
        {
            TreeNode* rightChild = node->right;
            node->right = node->left;
            node->left = NULL;
            TreeNode* p = node;
            while (p->right != NULL)
                p = p->right;
            p->right = rightChild;
        }
        expand(node->right);
    }
public:
    void flatten(TreeNode* root) {
        expand(root);
    }
};

class IterSolution {
public:
    void flatten(TreeNode* root) {
        TreeNode* node = root;
        TreeNode* rightChild;
        TreeNode* p;
        while (node != NULL)
        {
            if (node->left != NULL)
            {
                rightChild = node->right;
                node->right = node->left;
                node->left = NULL;
                p = node;
                while (p->right != NULL)
                    p = p->right;
                p->right = rightChild;
            }
            node = node->right;
        }
    }
};