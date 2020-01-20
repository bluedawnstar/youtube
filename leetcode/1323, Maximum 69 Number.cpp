// https://leetcode.com/problems/maximum-69-number/
// https://www.youtube.com/watch?v=2548yA1Re78

class Solution {
public:
    int maximum69Number(int num) {
        vector<int> digits;
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }

        for (int i = int(digits.size()) - 1; i >= 0; i--) {
            if (digits[i] == 6) {
                digits[i] = 9;
                break;
            }
        }

        int result = 0;
        for (int i = int(digits.size()) - 1; i >= 0; i--) {
            result = result * 10 + digits[i];
        }

        return result;
    }
};
