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

class Solution {
    void traverse(TreeNode* node, vector<vector<int>>* res, const int& level)
    {
        if (level >= res->size())
        {
            vector<int> levelStack;
            res->push_back(levelStack);
        }
        if (node != NULL)
        {
            (*res)[level].push_back(node->val);
            traverse(node->left, res, level + 1);
            traverse(node->right, res, level + 1);
        }
    }
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        traverse(root, &res, 0);
        if (!res.empty())
            if (res.back().empty())
                res.pop_back();
        return res;
    }
};

#include <queue>

class IterSolution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (root == NULL)
            return res;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        int i;
        int levelCount;
        while (!nodeQueue.empty())
        {
            vector<int> line;
            res.push_back(line);
            levelCount = nodeQueue.size();
            for (i = 0; i < levelCount; i++)
            {
                res[res.size() - 1].push_back(nodeQueue.back()->val);
                if (nodeQueue.back()->left != NULL)
                    nodeQueue.push(nodeQueue.back()->left);
                if (nodeQueue.back()->right != NULL)
                    nodeQueue.push(nodeQueue.back()->right);
                nodeQueue.pop();
            }
        }
        return res;
    }
};