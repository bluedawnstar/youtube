#pragma once

#include <vector>
#include <limits>
#include <algorithm>

struct SparseTable {
    // merge operation
    int merge(int left, int right) {
        return std::min(left, right);       // for min queries
        //return std::max(left, right);     // for max queries
        //return left + right;              // for sum queries
        //...
    }

    //---

    int N;
    std::vector<std::vector<int>> value;    // sparse table
    std::vector<int> H;                     // level

    void build(const int a[], int n) {
        this->N = n;
        
        // level table
        H.resize(n + 1);
        H[1] = 0;
        for (int i = 2; i < int(H.size()); i++)
            H[i] = H[i >> 1] + 1;

        // sparse table
        value.resize(H.back() + 1, std::vector<int>(n));
        for (int i = 0; i < n; i++)
            value[0][i] = a[i];
        for (int i = 1, step = 1; i < int(value.size()); i++, step <<= 1) {
            auto& prev = value[i - 1];
            auto& curr = value[i];
            for (int j = 0; j < n; j++) {
                if (j + step < n)
                    curr[j] = merge(prev[j], prev[j + step]);
                else
                    curr[j] = prev[j];
            }
        }
    }

    int query(int left, int right) {
        right++;
        int k = H[right - left];
        return merge(value[k][left], value[k][right - (1 << k)]);
    }

    //---

    int sum(int left, int right) {
        int size = right - left + 1;
        if (size < 0)
            return 0;

        int res = 0;
        while (size > 0) {
            int lastBit = size & -size;
            int level = H[lastBit];
            res += value[level][left]);

            left += lastBit;
            size -= lastBit;
        }

        return res;
    }
};
