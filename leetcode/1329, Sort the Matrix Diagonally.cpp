// https://leetcode.com/problems/sort-the-matrix-diagonally/
// https://youtu.be/gJA2ykdVmEE

// method #1 : O((n + m)*min(n,m)*log(min(n,m)))
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int n = int(mat.size());    // row
        int m = int(mat[0].size()); // col

        vector<vector<int>> res(n, vector<int>(m)); // res[n][m]

        // left side
        for (int i = 0; i < n; i++) {
            vector<int> v;
            for (int row = i, col = 0; row < n && col < m; row++, col++)
                v.emplace_back(mat[row][col]);
            sort(v.begin(), v.end());

            for (int row = i, col = 0, j = 0; row < n && col < m; row++, col++, j++)
                res[row][col] = v[j];
        }

        // top side
        for (int i = 1; i < m; i++) {
            vector<int> v;
            for (int row = 0, col = i; row < n && col < m; row++, col++)
                v.emplace_back(mat[row][col]);
            sort(v.begin(), v.end());

            for (int row = 0, col = i, j = 0; row < n && col < m; row++, col++, j++)
                res[row][col] = v[j];
        }

        return res;
    }
};

// method #2 : O(m * n + (n + m)*min(n,m)*log(min(n,m)))
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int n = int(mat.size());    // row
        int m = int(mat[0].size()); // col

        vector<vector<int>> res(n, vector<int>(m)); // res[n][m]

        unordered_map<int, vector<int>> M;           // [x] -> { ... }
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                M[row - col].push_back(mat[row][col]);
            }
        }

        for (auto& it : M) {
            sort(it.second.begin(), it.second.end());
        }

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                res[row][col] = M[row - col][min(row, col)];
            }
        }

        return res;
    }
};
