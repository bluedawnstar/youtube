// https://leetcode.com/problems/linked-list-in-binary-tree/
// https://youtu.be/Auh37w85fA0

// method #1 : O(n^2)
class Solution {
public:
    // O(n)
    bool checkPath(ListNode* list, TreeNode* node) {
        if (list == nullptr)
            return true;

        if (node == nullptr || node->val != list->val)
            return false;

        return checkPath(list->next, node->left) ||
            checkPath(list->next, node->right);
    }

    // O(n^2)
    bool isSubPath(ListNode* head, TreeNode* root) {
        if (root == nullptr)
            return false;
        if (checkPath(head, root))
            return true;

        return isSubPath(head, root->left) ||
            isSubPath(head, root->right);
    }
};

// method #2 : O(n*min(n,m))
class Solution {
public:
    unordered_map<int, vector<TreeNode*>> group;    // group[val] = { node1, node2, node3, ... }
    unordered_map<TreeNode*, TreeNode*> parent;     // parent[node] = parent of node

    // O(n)
    void dfs(TreeNode* node, TreeNode* parentNode) {
        if (node == nullptr)
            return;

        group[node->val].push_back(node);
        parent[node] = parentNode;
        dfs(node->left, node);
        dfs(node->right, node);
    }

    // O(n*min(n,m))
    bool isSubPath(ListNode* head, TreeNode* root) {
        // O(n)
        dfs(root, nullptr);

        // O(m)
        vector<int> list;
        for (ListNode* p = head; p; p = p->next)
            list.push_back(p->val);
        reverse(list.begin(), list.end());

        // O(n*min(n,m))
        for (TreeNode* startNode : group[list[0]]) {
            int i = 0;
            for (TreeNode* node = startNode; node && i < int(list.size()); node = parent[node], i++) {
                if (list[i] != node->val)
                    break;
            }
            if (i >= int(list.size()))
                return true;
        }
        return false;
    }
};
