// https://leetcode.com/problems/balance-a-binary-search-tree/
// https://youtu.be/FMMDSB6YSLo

// O(n)
class Solution {
public:
    void traverse(vector<TreeNode*>& output, TreeNode* node) {
        if (node == nullptr)
            return;
        traverse(output, node->left);
        output.push_back(node);
        traverse(output, node->right);
    }

    TreeNode* recBuild(const vector<TreeNode*>& nodes, int left, int right) {
        if (left > right)
            return nullptr;

        int mid = (left + right) / 2;
        //int mid = left + (right - left) / 2;
        nodes[mid]->left = recBuild(nodes, left, mid - 1);
        nodes[mid]->right = recBuild(nodes, mid + 1, right);
        return nodes[mid];
    }

    TreeNode* balanceBST(TreeNode* root) {
        vector<TreeNode*> nodes;
        traverse(nodes, root);

        return recBuild(nodes, 0, int(nodes.size()) - 1);
    }
};
