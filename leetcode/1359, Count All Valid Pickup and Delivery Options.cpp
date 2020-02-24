// https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/
// https://youtu.be/qtlIdNSgYFg

// method #1 : O(n)
class Solution {
public:
    int countOrders(int n) {
        const int MOD = 1000000007;

        long long res = 1;
        long long sum = 0;
        for (int i = 0; i < 2 * n; i += 2) {
            sum += i + (i + 1);
            if (sum >= MOD)
                sum -= MOD;
            res = res * sum % MOD;
        }

        return int(res);
    }
};

// method #2 : O(n)
class Solution {
public:
    int countOrders(int n) {
        const int MOD = 1000000007;

        long long res = 1;
        for (int i = 2; i <= 2 * n; i += 2) {
            res = (res * (i - 1) * i / 2) % MOD;
        }

        return int(res);
    }
};
