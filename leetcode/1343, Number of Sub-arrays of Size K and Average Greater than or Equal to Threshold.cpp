// https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/
// https://youtu.be/S4XKV2mrpXM

// sliding window, O(n)
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = int(arr.size());
        if (n < k)
            return 0;

        int res = 0;
        int sum = 0;
        int sumThreshold = threshold * k;

        for (int i = 0; i < k; i++)
            sum += arr[i];

        if (sum >= sumThreshold)
            res++;

        for (int i = k; i < n; i++) {
            sum += arr[i] - arr[i - k];
            if (sum >= sumThreshold)
                res++;
        }

        return res;
    }
};
