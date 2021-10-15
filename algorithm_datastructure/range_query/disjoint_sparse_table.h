#pragma once

#include <vector>
#include <limits>
#include <algorithm>

struct DisjointSparseTable {
    static const int DEFAULT_VALUE = 0;
    //static const int DEFAULT_VALUE = numeric_limits<int>::max();    // for min
    //static const int DEFAULT_VALUE = numeric_limits<int>::min();    // for max

    // merge operation
    int merge(int left, int right) {
        return left + right;            // sum
        //return std::min(left, right);   // min
        //return std::max(left, right);   // max
        //...
    }

    //---

    int N;
    std::vector<std::vector<int>> table;    // sparse table
    std::vector<int> H;                     // level

    void build(const int a[], int n) {
        N = 1;
        while (N < n)
            N <<= 1;

        // level table
        H.resize(N);
        H[1] = 0;
        for (int i = 2; i < int(H.size()); i++)
            H[i] = H[i >> 1] + 1;

        // disjoint sparse table
        table.resize(H.back() + 1, std::vector<int>(n, DEFAULT_VALUE));
        for (int i = 0; i < n; i++)
            table[0][i] = a[i];
        for (int h = 1, range = 4; range <= N; h++, range <<= 1) {
            int half = range >> 1;
            for (int i = half; i < N; i += range) {
                table[h][i - 1] = table[0][i - 1];
                for (int j = i - 2; j >= i - half; j--)
                    table[h][j] = merge(table[h][j + 1], table[0][j]);

                table[h][i] = table[0][i];
                for (int j = i + 1; j < i + half; j++)
                    table[h][j] = merge(table[h][j - 1], table[0][j]);
            }
        }
    }

    int query(int left, int right) {
        if (left == right)
            return table[0][left];

        int h = H[left ^ right];
        return merge(table[h][left], table[h][right]);
    }

    // O(N)
    void update(int index, int x) {
        table[0][index] = x;
        for (int h = 1, range = 4; range <= N; h++, range <<= 1) {
            int half = range >> 1;
            int start = index & ~(range - 1);
            if ((index & half) == 0) { // suffix
                table[h][index] = (index + 1 < (start | half)) ? merge(table[h][index + 1], x) : x;
                for (int i = index - 1; i >= start; i--)
                    table[h][i] = merge(table[h][i + 1], table[0][i]);
            } else { // prefix
                table[h][index] = (index > (start | half)) ? merge(table[h][index - 1], x) : x;
                for (int i = index + 1, next = start + range; i < next; i++)
                    table[h][i] = merge(table[h][i - 1], table[0][i]);
            }
        }
    }
};
