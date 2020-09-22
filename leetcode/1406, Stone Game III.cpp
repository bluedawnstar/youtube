// https://leetcode.com/problems/stone-game-iii/
// https://youtu.be/jTK_P6_Zalg

// method #1 : min-max, O(n)
class Solution {
public:
    const int INF = 0x3f3f3f3f;

    vector<vector<int>> dp;

    // return alice score
    int minmax(vector<int>& stoneValue, int start, bool alice) {
        int N = int(stoneValue.size());
        if (start >= N)
            return 0;
        else if (start + 1 == N)
            return alice ? stoneValue[start] : 0;

        int res = alice ? -INF : INF;
        if (dp[alice][start] != res)
            return dp[alice][start];

        if (alice) {
            int s = 0;
            for (int i = start, limit = min(N, start + 3); i < limit; i++) {
                s += stoneValue[i];
                res = max(res, s + minmax(stoneValue, i + 1, !alice));
            }
        } else {
            for (int i = start, limit = min(N, start + 3); i < limit; i++) {
                res = min(res, minmax(stoneValue, i + 1, !alice));
            }
        }

        return dp[alice][start] = res;
    }

    string stoneGameIII(vector<int>& stoneValue) {
        int sum = 0;
        for (int i = 0; i < int(stoneValue.size()); i++)
            sum += stoneValue[i];

        int N = int(stoneValue.size());
        dp.resize(2);
        dp[0].assign(N, INF);
        dp[1].assign(N, -INF);

        int alice = minmax(stoneValue, 0, true);
        if (alice > sum - alice)
            return "Alice";
        else if (alice < sum - alice)
            return "Bob";
        else
            return "Tie";
    }
};

// method #2 : recursive DP, O(n)
class Solution {
public:
    const int INF = 0x3f3f3f3f;

    vector<int> dp;

    int rec(vector<int>& stoneValue, int start) {
        int N = int(stoneValue.size());
        if (start >= N)
            return 0;

        if (dp[start] != -INF)
            return dp[start];

        int res = -INF;
        int s = 0;
        for (int i = start, limit = min(N, start + 3); i < limit; i++) {
            s += stoneValue[i];
            res = max(res, s - rec(stoneValue, i + 1));
        }

        return dp[start] = res;
    }

    string stoneGameIII(vector<int>& stoneValue) {
        int sum = 0;
        for (int i = 0; i < int(stoneValue.size()); i++)
            sum += stoneValue[i];

        dp.assign(stoneValue.size(), -INF);

        //int res = rec(stoneValue, 0);
        rec(stoneValue, 0);
        int res = dp[0];

        if (res > 0)
            return "Alice";
        else if (res < 0)
            return "Bob";
        else
            return "Tie";
    }
};

// method #3 : DP, O(n)
class Solution {
public:
    const int INF = 0x3f3f3f3f;

    string stoneGameIII(vector<int>& stoneValue) {
        int N = int(stoneValue.size());
        vector<int> dp(N + 1, -INF);
        dp[N] = 0;

        for (int i = N - 1; i >= 0; i--) {
            int s = 0;
            for (int j = i, limit = min(N, i + 3); j < limit; j++) {
                s += stoneValue[j];
                dp[i] = max(dp[i], s - dp[j + 1]);
            }
        }

        if (dp[0] > 0)
            return "Alice";
        else if (dp[0] < 0)
            return "Bob";
        else
            return "Tie";
    }
};
