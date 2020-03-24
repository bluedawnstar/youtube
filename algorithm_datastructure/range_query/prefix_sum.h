#pragma once

struct PrefixSum {
    vector<int> sum;

    void build(const int in[], int n) {
        sum.resize(n + 1);
        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + in[i - 1];
        }
    }

    // O(n)
    void build(const vector<int>& in) {
        build(in.data(), int(in.size()));
    }

    // 0 <= left <= right < n, inclusive, O(1)
    int query(int left, int right) const {
        return sum[right + 1] - sum[left];
    }
};
