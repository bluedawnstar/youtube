// https://leetcode.com/problems/remove-palindromic-subsequences/
// https://youtu.be/6CvzjAt9oi0

// O(n)
class Solution {
public:
    int removePalindromeSub(string s) {
        int n = int(s.length());
        if (n == 0)
            return 0;

        for (int i = 0, j = n - 1; i < j; i++, j--) {
            if (s[i] != s[j])
                return 2;
        }

        return 1;
    }
};
