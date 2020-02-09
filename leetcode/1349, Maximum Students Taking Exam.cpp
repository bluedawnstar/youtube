// https://leetcode.com/problems/maximum-students-taking-exam/
// https://youtu.be/4nHdArZC7BA

// method #1 : memoization, O(m*4^n)
class Solution {
public:
    int rec(const vector<int>& broken, vector<vector<int>>& dp, int m, int n, int prevMask, int row) {
        if (row >= m)
            return 0;

        if (dp[row][prevMask] >= 0)
            return dp[row][prevMask];

        int res = 0;
        for (int currMask = 0; currMask < (1 << n); currMask++) {
            if ((currMask & broken[row]) != 0
                || (currMask & (currMask << 1)) != 0)
                continue;
            if ((prevMask & (currMask << 1)) != 0 || (prevMask & (currMask >> 1)) != 0)
                continue;

            int bitCnt = 0;
            for (int t = currMask; t; t &= t - 1)
                bitCnt++;

            res = max(res, rec(broken, dp, m, n, currMask, row + 1) + bitCnt);
        }

        return dp[row][prevMask] = res;
    }

    int maxStudents(vector<vector<char>>& seats) {
        int m = int(seats.size());
        int n = int(seats[0].size());

        vector<int> broken(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '#')
                    broken[i] |= 1 << j;
            }
        }

        // dp[row][mask]
        vector<vector<int>> dp(m, vector<int>(1 << n, -1));
        return rec(broken, dp, m, n, 0, 0);
    }
};

// method #2 : DP, O(m*4^n)
class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = int(seats.size());
        int n = int(seats[0].size());

        vector<int> broken(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (seats[i][j] == '#')
                    broken[i] |= 1 << j;
            }
        }

        // dp[row][mask]
        vector<vector<int>> dp(m + 1, vector<int>(1 << n, 0));
        for (int i = 1; i <= m; i++) {
            for (int currMask = 0; currMask < (1 << n); currMask++) {
                if ((currMask & broken[i - 1]) != 0 || (currMask & (currMask << 1)) != 0)
                    continue;

                int bitCnt = 0;
                for (int t = currMask; t; t &= t - 1)
                    bitCnt++;

                for (int prevMask = 0; prevMask < (1 << n); prevMask++) {
                    if ((prevMask & (currMask << 1)) != 0 || (prevMask & (currMask >> 1)) != 0)
                        continue;
                    dp[i][currMask] = max(dp[i][currMask], dp[i - 1][prevMask] + bitCnt);
                }
            }
        }

        //int res = 0;
        //for (int i = 0; i < (1 << n); i++)
        //    res = max(res, dp[m][i]);
        //return res;
        return *max_element(dp[m].begin(), dp[m].end());
    }
};
