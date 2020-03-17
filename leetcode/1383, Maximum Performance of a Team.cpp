// https://leetcode.com/problems/maximum-performance-of-a-team/
// https://youtu.be/crWQCiQUp_M

// O(n*logn)
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<pair<int, int>> values;  // (efficiency, speed)

        for (int i = 0; i < n; i++)
            values.emplace_back(efficiency[i], speed[i]);
        sort(values.begin(), values.end(), greater<pair<int, int>>());  // descending order

        long long res = 0;

        long long speedSum = 0;
        priority_queue<int> Q;
        for (int i = 0; i < n; i++) {
            speedSum += values[i].second;
            res = max(res, speedSum * values[i].first);

            Q.push(-values[i].second);
            if (Q.size() == k) {
                speedSum += Q.top();
                Q.pop();
            }
        }

        return int(res % 1'000'000'007);
    }
};
