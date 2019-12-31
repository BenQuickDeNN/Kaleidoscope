#include <vector>
#include <cstdlib>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 递归法
class Solution {
    void traverse(const TreeNode* p, vector<int>* res)
    {
        if (p == NULL)
            return;
        if (p->left != NULL)
            traverse(p->left, res);
        res->push_back(p->val);
        if (p->right != NULL)
            traverse(p->right, res);
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        traverse(root, &res);
        return res;
    }
};

// 迭代法
class Solution_Iter {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        vector<TreeNode*> nodeStack = {root};
        while (!nodeStack.empty())
        {
            if (nodeStack.back() == NULL)
            {
                nodeStack.pop_back();
                continue;
            }
            if (nodeStack.back()->left != NULL)
            {
                nodeStack.push_back(nodeStack.back()->left);
                nodeStack[nodeStack.size() - 2]->left = NULL;
                continue;
            }
            res.push_back(nodeStack.back()->val);
            if (nodeStack.back()->right != NULL)
            {
                nodeStack.push_back(nodeStack.back()->right);
                nodeStack[nodeStack.size() - 2] = NULL;
                continue;
            }
            nodeStack.pop_back();
        }
        return res;
    }
};