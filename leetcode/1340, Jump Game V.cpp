// https://leetcode.com/problems/jump-game-v/
// https://youtu.be/tXLNOkOAVQY

// DP, O(n)
class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = int(arr.size());

        // low value first
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++)
            v.emplace_back(arr[i], i);
        sort(v.begin(), v.end());

        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            int x = v[i].first;
            int idx = v[i].second;

            int L = max(0, idx - d);
            int R = min(n - 1, idx + d);
            int maxStep = 0;
            for (int j = idx - 1; j >= L; j--) {
                if (arr[j] >= x)
                    break;
                maxStep = max(maxStep, dp[j]);
            }
            for (int j = idx + 1; j <= R; j++) {
                if (arr[j] >= x)
                    break;
                maxStep = max(maxStep, dp[j]);
            }
            dp[idx] = maxStep + 1;
        }

        return *max_element(dp.begin(), dp.end());  // maximum number
    }
};
