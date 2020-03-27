#pragma once

struct BinaryIndexedTree2D {
    vector<vector<int>> tree;

    BinaryIndexedTree2D(int rowN, int colN) : tree(rowN + 1, vector<int>(colN + 1)) {
    }

    
    void add(int row, int col, int val) {
        row++;
        col++;

        for (int r = row; r < int(tree.size()); r += r & -r) {
            for (int c = col; c < int(tree[row].size()); c += c & -c)
                tree[r][c] += val;
        }
    }


    int sum(int row, int col) const {
        row++;
        col++;

        int res = 0;
        for (int r = row; r > 0; r &= r - 1) {
            for (int c = col; c > 0; c &= c - 1)
                res += tree[r][c];
        }

        return res;
    }

    int sumRange(int row1, int col1, int row2, int col2) const {
        int res = sum(row2, col2);
        if (row1 > 0)
            res -= sum(row1 - 1, col2);
        if (col1 > 0)
            res -= sum(row2, col1 - 1);
        if (row1 > 0 && col1 > 0)
            res += sum(row1 - 1, col1 - 1);
        return res;
    }
};
