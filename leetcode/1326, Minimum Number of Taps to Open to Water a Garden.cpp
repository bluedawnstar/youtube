// https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/

// method #1 : O(nlogn)
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<pair<int, int>> R;
        for (int i = 0; i <= n; i++)
            R.emplace_back(i - ranges[i], i + ranges[i]);

        sort(R.begin(), R.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first;
        });

        int res = 1;

        int currReach = 0;
        int maxReach = 0;
        for (int i = 0; i <= n && maxReach < n; i++) {
            if (R[i].first > maxReach)
                return -1;

            if (R[i].first > currReach) {
                res++;
                currReach = maxReach;
            }
            maxReach = max(maxReach, R[i].second);
        }

        return res;
    }
};

// method #2 : O(n)
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> reach(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            int left = max(0, i - ranges[i]);
            int right = i + ranges[i];
            reach[left] = max(reach[left], right);
        }

        int res = 1;

        int currReach = 0;
        int maxReach = 0;
        for (int x = 0; x <= n && maxReach < n; x++) {
            if (x > maxReach)
                return -1;

            if (x > currReach) {
                res++;
                currReach = maxReach;
            }
            maxReach = max(maxReach, reach[x]);
        }

        return res;
    }
};
