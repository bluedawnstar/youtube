// https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/
// https://youtu.be/S4XKV2mrpXM

// O(log(num))
class Solution {
public:
    int numberOfSteps(int num) {
        int res = 0;
        while (num) {
            if (num & 1)
                num--;
            else
                num >>= 1;
            res++;
        }
        return res;
    }
};
