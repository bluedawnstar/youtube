// https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/
// https://youtu.be/tXLNOkOAVQY

// recursive solution, O(nlogn)
class Solution {
public:
    const int MOD = 1000000007;

    int totalSum = 0;
    long long ans = 0;

    int recSum(TreeNode* node) {
        if (!node)
            return 0;

        int res = 0;
        res += recSum(node->left);
        res += recSum(node->right);
        res += node->val;

        return res;
    }

    int recSolve(TreeNode* node) {
        if (!node)
            return 0;

        int leftSum = recSolve(node->left);
        int rightSum = recSolve(node->right);

        ans = max(ans, 1ll * leftSum * (totalSum - leftSum));
        ans = max(ans, 1ll * rightSum * (totalSum - rightSum));

        return leftSum + rightSum + node->val;
    }

    int maxProduct(TreeNode* root) {
        totalSum = recSum(root);
        recSolve(root);
        return int(ans % MOD);
    }
};
