// https://leetcode.com/problems/minimum-window-substring/
// https://youtu.be/f9xL16rv9K8

// LeetCode 76 - Minimum Window Substring
class Solution {
public:
    // O(n)
    string minWindow(string s, string t) {
        int n = int(s.length());

        int m = 0;          // the number of unique character in t
        vector<int> req(256);
        for (auto c : t) {
            if (++req[c] == 1)
                m++;
        }

        string res;

        int charCount = 0;  // req를 만족시키는 글자의 개수
        vector<int> cnt(256);
        for (int L = 0, R = 0; R < n; R++) {
            // update right
            if (++cnt[s[R]] == req[s[R]])
                charCount++;

            // update left
            if (charCount == m) {
                do {
                    int c = s[L++];
                    if (--cnt[c] < req[c])
                        charCount--;
                } while (charCount == m);

                // update answer - [L-1, R]
                int len = R - L + 2;
                if (res.empty() || res.length() > len)
                    res = s.substr(L - 1, len);
            }
        }

        return res;
    }
};
