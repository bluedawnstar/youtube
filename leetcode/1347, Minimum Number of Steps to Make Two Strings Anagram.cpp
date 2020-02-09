// https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/
// https://youtu.be/kc_i0O7MvBU

// O(n)
class Solution {
public:
    int minSteps(string s, string t) {
        int n = int(s.length());

        vector<int> cntS(26), cntT(26);
        for (int i = 0; i < n; i++) {
            cntS[s[i] - 'a']++;
            cntT[t[i] - 'a']++;
        }

        int res = 0;
        for (int i = 0; i < 26; i++)
            res += abs(cntS[i] - cntT[i]);

        return res / 2;
    }
};
