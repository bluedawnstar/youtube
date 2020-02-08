// https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/
// https://youtu.be/tXLNOkOAVQY

// O(n*m + nlogn)
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        int n = int(mat.size());
        int m = int(mat[0].size());
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) {
            int one = 0;
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0)
                    break;
                one++;
            }
            v.emplace_back(one, i);
        }
        sort(v.begin(), v.end());
        vector<int> res;
        for (int i = 0; i < k; i++)
            res.push_back(v[i].second);
        return res;
    }
};
