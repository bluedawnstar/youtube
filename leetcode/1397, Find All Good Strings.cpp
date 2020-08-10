// https://leetcode.com/problems/find-all-good-strings/
// https://youtu.be/P6PIeUY0cL4

class Solution {
public:
    static const int MOD = 1'000'000'007;

    vector<int> prefixFunction(const string& s) {
        int n = int(s.length());
        vector<int> pi(n);

        int j = 0;
        for (int i = 1; i < n; i++) {
            while (j > 0 && s[j] != s[i])
                j = pi[j - 1];

            if (s[j] == s[i])
                j++;
            pi[i] = j;
        }

        return pi;
    }

    // O(n * m)
    int findGoodStrings(int n, string s, string evil, bool includeFit) {
        int m = int(evil.length());

        // repeat length
        vector<int> pi = prefixFunction(evil);
        int rep = m - pi[m - 1];

        vector<int> dpFit(n + 1);
        vector<int> dpLess(n + 1);

        vector<int> dpMinusLess(n + 1);

        dpFit[0] = 1;
        dpLess[0] = 0;
        for (int i = 1; i <= n; i++) {
            dpFit[i] = dpFit[i - 1];
            dpLess[i] = int((1ll * dpFit[i - 1] * (s[i - 1] - 'a') + dpLess[i - 1] * 26ll) % MOD);

            if (i >= m) {
                if (evil == s.substr(i - m, m))
                    dpFit[i] = 0;

                if (evil < s.substr(i - m, m))
                    dpMinusLess[i] = (dpFit[i - m] + dpLess[i - m]) % MOD;
                else
                    dpMinusLess[i] = dpLess[i - m];

                if (rep < m) {
                    dpMinusLess[i] -= dpMinusLess[i - rep];
                    if (dpMinusLess[i] < 0)
                        dpMinusLess[i] += MOD;
                }

                dpLess[i] -= dpMinusLess[i];
                if (dpLess[i] < 0)
                    dpLess[i] += MOD;
            }
        }

        int res = dpLess[n];
        if (includeFit) {
            res += dpFit[n];
            if (res >= MOD)
                res -= MOD;
        }

        return res;
    }

    int findGoodStrings(int n, string s1, string s2, string evil) {
        int ans = findGoodStrings(n, s2, evil, true) - findGoodStrings(n, s1, evil, false);
        if (ans < 0)
            ans += MOD;
        return ans;
    }
};
