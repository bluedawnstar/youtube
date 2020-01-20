// https://leetcode.com/problems/delete-leaves-with-a-given-value/
// https://youtu.be/bRcL2SbAcZA

/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
// method #1
class Solution {
public:
    TreeNode * dfs(TreeNode* node, int target) {
        if (node == nullptr)
            return nullptr;

        node->left = dfs(node->left, target);
        node->right = dfs(node->right, target);

        if (node->left == nullptr && node->right == nullptr && node->val == target) {
            //delete node;
            return nullptr;
        } else
            return node;
    }

    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        return dfs(root, target);
    }
};

// method #2
class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* node, int target) {
        if (node == nullptr)
            return nullptr;

        node->left = removeLeafNodes(node->left, target);
        node->right = removeLeafNodes(node->right, target);

        if (node->left == nullptr && node->right == nullptr && node->val == target) {
            //delete node;
            return nullptr;
        } else
            return node;
    }
};
