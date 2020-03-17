// https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/
// https://youtu.be/5W7LlybzdD4

// O(n)
class Solution {
public:
    int ans;

    void rec(TreeNode* node, bool right, int depth) {
        if (node == nullptr) {
            ans = max(ans, depth);
            return;
        }

        if (right)
            rec(node->left, false, depth + 1);
        else
            rec(node->left, false, 0);

        if (right)
            rec(node->right, true, 0);
        else
            rec(node->right, true, depth + 1);
    }

    int longestZigZag(TreeNode* root) {
        ans = 0;
        rec(root->left, false, 0);  // left
        rec(root->right, true, 0);  // right
        return ans;
    }
};

