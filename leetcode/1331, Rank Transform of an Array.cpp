// https://leetcode.com/problems/rank-transform-of-an-array/
// 

// O(nlogn)
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = int(arr.size());

        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);    // idx = { 0, 1, 2, ..., n - 1 }
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return arr[a] < arr[b];
        });

        vector<int> res(n);
        for (int i = 0, rank = 1; i < n; i++) {
            if (i == 0 || arr[idx[i - 1]] == arr[idx[i]])
                res[idx[i]] = rank;
            else
                res[idx[i]] = ++rank;
        }

        return res;
    }
};
