// https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/
// https://youtu.be/kYffNXU7CQo

// O(n)
class Solution {
public:
    const int INF = 0x3f3f3f3f;

    int ans;

    // (min, max, sum)
    tuple<int, int, int> rec(TreeNode* node) {
        if (node == nullptr)
            return make_tuple(INF, -INF, 0);

        int leftMin, leftMax, leftSum;
        tie(leftMin, leftMax, leftSum) = rec(node->left);

        int rightMin, rightMax, rightSum;
        tie(rightMin, rightMax, rightSum) = rec(node->right);

        if (leftMax < node->val && node->val < rightMin) {
            int sum = leftSum + node->val + rightSum;
            int minVal = min(leftMin, node->val);
            int maxVal = max(rightMax, node->val);
            ans = max(ans, sum);
            return make_tuple(minVal, maxVal, sum);
        }

        return make_tuple(-INF, INF, 0);
    }

    int maxSumBST(TreeNode* root) {
        ans = 0;
        rec(root);
        return ans;
    }
};
