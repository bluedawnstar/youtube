// https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
// https://youtu.be/eMBakNiUyyw

// method #1 : DP, O(d*n^2)
class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        const int INF = 0x3f3f3f3f;

        int n = int(jobDifficulty.size());

        // dp[day][right], 1 <= day <= d, 1 <= right <= n
        vector<vector<int>> dp(d + 1, vector<int>(n + 1, INF));

        dp[0][0] = 0;
        for (int i = 1; i <= d; i++) {
            for (int right = i; right <= n; right++) {
                int maxDifficulty = 0;
                for (int left = right; left >= i; left--) {
                    maxDifficulty = max(maxDifficulty, jobDifficulty[left - 1]);
                    dp[i][right] = min(dp[i][right], dp[i - 1][left - 1] + maxDifficulty);
                }
            }
        }

        if (dp[d][n] >= INF)
            return -1;
        return dp[d][n];
    }
};

// method #2 : memoization, O(d*n^2)
class Solution {
public:
    const int INF = 0x3f3f3f3f;

    vector<vector<int>> dp;

    int rec(vector<int>& jobDifficulty, int d, int right) {
        if (d <= 0)
            return right <= 0 ? 0 : INF;

        if (dp[d][right] < INF)
            return dp[d][right];

        int res = INF;

        int maxD = 0;
        for (int i = right; i > 0; i--) {
            maxD = max(maxD, jobDifficulty[i - 1]);
            res = min(res, rec(jobDifficulty, d - 1, i - 1) + maxD);
        }

        return dp[d][right] = res;
    }

    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = int(jobDifficulty.size());
        dp = vector<vector<int>>(d + 1, vector<int>(n + 1, INF));

        int ans = rec(jobDifficulty, d, n);
        if (ans >= INF)
            return -1;
        return ans;
    }
};
