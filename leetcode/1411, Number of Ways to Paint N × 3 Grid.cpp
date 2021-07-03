// https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/
// https://youtu.be/rrhquJDbZOA

const int MOD = 1'000'000'007;


//--- method #1 : O(n) --------------------------------------------------------

class Solution {
public:
    // O(n)
    int numOfWays(int n) {
        // int dp[n][3*3*3]
        vector<vector<int>> dp(n, vector<int>(3*3*3));

        for (int curr = 0; curr < 27; curr++) {
            int a = curr / 9, b = (curr % 9) / 3, c = curr % 3;
            if (a != b && b != c)
                dp[0][curr] = 1;
        }

        for (int i = 1; i < n; i++) {
            for (int prev = 0; prev < 27; prev++) {
                int a = prev / 9, b = (prev % 9) / 3, c = prev % 3;
                if (a == b || b == c)
                    continue;

                for (int curr = 0; curr < 27; curr++) {
                    int d = curr / 9, e = (curr % 9) / 3, f = curr % 3;
                    if (d == e || e == f)
                        continue;
                    if (a == d || b == e || c == f)
                        continue;

                    dp[i][curr] += dp[i - 1][prev];
                    if (dp[i][curr] >= MOD)
                        dp[i][curr] -= MOD;
                }
            }
        }

        int res = 0;
        for (int i = 0; i < 27; i++) {
            res += dp[n - 1][i];
            if (res >= MOD)
                res -= MOD;
        }

        return res;
    }
};


//--- method #2 : O(n) --------------------------------------------------------

class Solution {
public:
    // O(n)
    int numOfWays(int n) {
        int aba = 6, abc = 6;

        for (int i = 1; i < n; i++) {
            int aba2 = (aba * 3ll + abc * 2ll) % MOD;
            int abc2 = (aba * 2ll + abc * 2ll) % MOD;
            aba = aba2;
            abc = abc2;
        }

        return (aba + abc) % MOD;
    }
};


//--- method #3 : O(logn) -----------------------------------------------------

/*
   | a00  a01 |
   | a10  a11 |
*/
struct Mat2x2 {
    long long a00, a01; // 64bit
    long long a10, a11;

    Mat2x2() {
        /*
          | 1 0 |
          | 0 1 |
        */
        a00 = a01 = 1;
        a10 = a11 = 0;
    }

    Mat2x2(long long _a00, long long _a01, long long _a10, long long _a11) {
        a00 = _a00;
        a01 = _a01;
        a10 = _a10;
        a11 = _a11;
    }

    Mat2x2 operator *(const Mat2x2& rhs) const {
        /*
           | a00  a01 | | a00  a01 |
           | a10  a11 | | a10  a11 |
        */
        return Mat2x2((a00 * rhs.a00 + a01 * rhs.a10) % MOD,
            (a00 * rhs.a01 + a01 * rhs.a11) % MOD,
            (a10 * rhs.a00 + a11 * rhs.a10) % MOD,
            (a10 * rhs.a01 + a11 * rhs.a11) % MOD);
    }
};

Mat2x2 pow(const Mat2x2& m, int n) {
    if (n == 0)
        return Mat2x2();
    else if (n == 1)
        return m;

    auto m2 = pow(m, n / 2);

    Mat2x2 res = m2 * m2;
    if (n & 1)
        res = res * m;

    return res;
}

class Solution {
public:
    // O(logn)
    int numOfWays(int n) {
        Mat2x2 mat = pow(Mat2x2{ 3, 2, 2, 2 }, n - 1);

        /*
          | a00 a01 | | 6 |
          | a10 a11 | | 6 |
        */
        long long aba = mat.a00 * 6 + mat.a01 * 6;
        long long abc = mat.a10 * 6 + mat.a11 * 6;

        return (aba + abc) % MOD;
    }
};
