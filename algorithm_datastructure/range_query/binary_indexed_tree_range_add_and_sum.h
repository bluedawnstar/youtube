#pragma once

#include "binary_indexed_tree.h"

// - for sum from 0 to pos
// - f(x) = mul * x + add
struct BinaryIndexedTreeMultAdd {
    BinaryIndexedTree mul;
    BinaryIndexedTree add;

    BinaryIndexedTreeMultAdd() {
    }

    explicit BinaryIndexedTreeMultAdd(int n) : mul(n), add(n) {
    }


    void init(int n) {
        mul.init(n);
        add.init(n);
    }


    void add(int x, int d) {
        mul.add(x, d);
        add.add(x, d * (1 - x));
    }

    // O(logn)
    void addRange(int left, int right, int d) {
        add(left, d);
        add(right + 1, -d);
    }

    // sum[0, x], O(logn)
    int sum(int x) const {
        return add.sum(x) + mul.sum(x) * x;
    }

    // sum[left, right], O(logn)
    int sumRange(int left, int right) const {
        return sum(right) - sum(left - 1);
    }
};
