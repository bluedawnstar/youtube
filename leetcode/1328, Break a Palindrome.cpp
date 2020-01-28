// https://leetcode.com/problems/break-a-palindrome/
// https://youtu.be/UwaoswYb5bk

// O(n)
class Solution {
public:
    string breakPalindrome(string palindrome) {
        int n = int(palindrome.length());
        if (n == 1)
            return "";

        int half = n / 2;
        for (int i = 0; i < half; i++) {
            if (palindrome[i] != 'a') {
                palindrome[i] = 'a';
                return palindrome;
            }
        }

        // "a...a [x] a...a" -> "a...a [x] a...b"
        palindrome.back() = 'b';
        return palindrome;
    }
};
