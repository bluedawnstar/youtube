// https://leetcode.com/problems/construct-target-array-with-multiple-sums/
// https://youtu.be/9F5AFgLapQc

// O(nlogn)
class Solution {
public:
    bool isPossible(vector<int>& target) {
        int n = int(target.size());

        priority_queue<long long> Q;    // long long = 64bit integer, Q = max heap
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += target[i];
            if (target[i] > 1)
                Q.push(target[i]);
        }

        while (!Q.empty()) {
            long long x = Q.top();
            Q.pop();

            long long a = 2 * x - sum;
            if (a <= 0)
                return false;

            long long nextMaxX;
            if (Q.empty())
                nextMaxX = 1;
            else
                nextMaxX = Q.top() - 1;

            long long r = sum % (sum - x);
            a = ((nextMaxX - r) / (sum - x)) * (sum - x) + r;

            if (a > 1)
                Q.push(a);
            sum = (sum - x) + a;
        }

        return true;
    }
};
