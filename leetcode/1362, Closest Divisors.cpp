// https://leetcode.com/problems/closest-divisors/
// https://youtu.be/71uTrZFycx0

// O(sqrt(num))
class Solution {
public:
    pair<int, int> findFactor(int x) {
        int sqrtN = int(sqrt(x));
        for (int i = sqrtN; i > 1; i--) {
            if (x % i == 0)
                return pair<int, int>(i, x / i);
        }
        return pair<int, int>(1, x);
    }

    vector<int> closestDivisors(int num) {
        pair<int, int> res1 = findFactor(num + 1);
        pair<int, int> res2 = findFactor(num + 2);

        if (res1.second - res1.first <= res2.second - res2.first)
            return vector<int>{ res1.first, res1.second };
        else
            return vector<int>{ res2.first, res2.second };
    }
};
