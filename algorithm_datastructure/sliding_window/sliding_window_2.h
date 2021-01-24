// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// https://youtu.be/xzRYqeoPyLk

// LeetCode 3 - Longest Substring Without Repeating Characters
class Solution {
public:
    // O(n)
    int lengthOfLongestSubstring(string s) {
        int n = int(s.length());

        int res = 0;
        vector<int> cnt(256);
        for (int L = 0, R = 0; R < n; R++) {
            // update right
            cnt[s[R]]++;

            // updat left
            while (cnt[s[R]] > 1)
                cnt[s[L++]]--;

            // update answer
            res = max(res, R - L + 1);
        }

        return res;
    }
};
