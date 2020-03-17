// https://leetcode.com/problems/time-needed-to-inform-all-employees/
// https://youtu.be/DB0Lq7hxNXE

// O(n)
class Solution {
public:
    int rec(const vector<int>& informTime, const vector<vector<int>>& tree, int id) {
        int res = 0;
        for (auto child : tree[id])
            res = max(res, rec(informTime, tree, child));
        return res + informTime[id];
    }

    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<vector<int>> tree(n);
        for (int i = 0; i < n; i++) {
            if (manager[i] >= 0)
                tree[manager[i]].push_back(i);
        }

        return rec(informTime, tree, headID);
    }
};

