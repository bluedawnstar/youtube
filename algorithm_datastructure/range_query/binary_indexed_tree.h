#pragma once

struct BinaryIndexedTree {
    vector<int> tree;

    explicit BinaryIndexedTree(int n) : tree(n + 1) {
    }

    // O(logN)
    void add(int pos, int val) {
        pos++;
        while (pos < int(tree.size())) {
            tree[pos] += val;
            pos += pos & -pos;      // add lowest bit
        }
    }

    // sum from 0 to pos, O(logN)
    int sum(int pos) const {
        pos++;

        int res = 0;
        while (pos > 0) {
            res += tree[pos];
            pos &= pos - 1;         // clear lowest bit
        }

        return res;
    }

    // inclusive, O(logN)
    int sumRange(int left, int right) const {
        int res = sum(right);
        if (left > 0)
            res -= sum(left - 1);
        return res;
    }
};
