// https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/
// https://youtu.be/efAEJ-z6Fww

// method #1 : O(n)
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = int(s.length());

        int result = 0;
        int lastPos[3] = { -1, -1, -1 };
        for (int i = 0; i < n; i++) {
            lastPos[s[i] - 'a'] = i;
            result += min(lastPos[0], min(lastPos[1], lastPos[2])) + 1;
        }

        return result;
    }
};

// method #2 : sliding window, O(n)
int numberOfSubstrings(string s) {
    int n = int(s.length());

    int res = 0;

    int usedChar = 0;
    int charCount[3] = { 0, 0, 0 };
    for (int L = 0, R = 0; R < n; R++) {
        if (++charCount[s[R] - 'a'] == 1 && ++usedChar == 3) {
            while (usedChar >= 3) {
                if (--charCount[s[L++] - 'a'] == 0)
                    usedChar--;
            }
        }
        res += L;
    }

    return res;
}
