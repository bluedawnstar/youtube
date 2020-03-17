// https://leetcode.com/problems/frog-position-after-t-seconds/
// https://youtu.be/q0nHODCrt_s

// O(n)
class Solution {
public:
    double dfs(const vector<vector<int>>& tree, int t, int target, int u, int parent) {
        if (t == 0)
            return u == target ? 1.0 : 0.0;

        double res = 0.0;
        int childCount = 0;
        for (auto v : tree[u]) {
            if (v != parent) {
                if (res == 0.0)
                    res = dfs(tree, t - 1, target, v, u);
                childCount++;
            }
        }

        if (childCount == 0)
            return u == target ? 1.0 : 0.0;
        return res / childCount;
    }

    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        if (n == 1)
            return 1.0;

        vector<vector<int>> tree(n);
        for (auto e : edges) {
            tree[e[0] - 1].push_back(e[1] - 1);
            tree[e[1] - 1].push_back(e[0] - 1);
        }

        return dfs(tree, t, target - 1, 0, -1);
    }
};
