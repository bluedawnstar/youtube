#pragma once

#include <math.h>
#include <vector>
#include <limits>
#include <algorithm>

struct SqrtTree {
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

    int                 N;
    int                 blockSize;
    int                 blockCount;

    vector<int>         prefix;             // prefix array
    vector<int>         suffix;             // suffix array

    // disjoint sparse tables
    vector<int>         H;
    vector<vector<int>> blockSpTable;       // disjoint sparse table of block values
    vector<vector<int>> spTablesOfBlocks;   // disjoint sparse tables of each blocks

    // O(N*logN)
    void build(const int a[], int n) {
        N = n;

        int sqrtN = int(sqrt(n));
        blockSize = 1;
        while (blockSize < sqrtN)
            blockSize <<= 1;
        blockCount = (N + blockSize - 1) / blockSize;

        buildPrefixSuffix(a);
        buildSparseTable(a);
    }

    void build(const vector<int>& a) {
        build(&a[0], int(a.size()));
    }


    // O(1), inclusive
    int query(int left, int right) {
        if (left == right)
            return spTablesOfBlocks[0][left];

        int blockL = left / blockSize;
        int blockR = right / blockSize;

        if (blockL == blockR) {
            int h = H[left ^ right];
            return merge(spTablesOfBlocks[h][left], spTablesOfBlocks[h][right]);
        }

        int res = merge(suffix[left], prefix[right]);
        if (blockL + 1 < blockR) {
            if (++blockL == --blockR)
                res = merge(res, blockSpTable[0][blockL]);
            else {
                int h = H[blockL ^ blockR];
                res = merge(res, merge(blockSpTable[h][blockL], blockSpTable[h][blockR]));
            }
        }
        return res;
    }

    // O(sqrt(N))
    void update(int index, int x) {
        spTablesOfBlocks[0][index] = x;
        updatePrefixSuffix(index);
        updateSparseTable(index);
    }

private:
    // O(N)
    void buildPrefixSuffix(const int a[]) {
        prefix.resize(N);
        suffix.resize(N);
        for (int i = 0; i < blockCount; i++) {
            int first = i * blockSize;
            int last = min(first + blockSize, N) - 1;

            prefix[first] = a[first];
            for (int j = first + 1; j <= last; j++)
                prefix[j] = merge(prefix[j - 1], a[j]);

            suffix[last] = a[last];
            for (int j = last - 1; j >= first; j--)
                suffix[j] = merge(suffix[j + 1], a[j]);
        }
    }

    void buildSparseTable(vector<vector<int>>& table) {
        int size = int(table[0].size());
        for (int h = 1, range = 4; h < int(table.size()); h++, range <<= 1) {
            int half = range >> 1;
            for (int i = half; i < size; i += range) {
                table[h][i - 1] = table[0][i - 1];
                for (int j = i - 2; j >= i - half; j--)
                    table[h][j] = merge(table[h][j + 1], table[0][j]);

                table[h][i] = table[0][i];
                for (int j = i + 1; j < i + half; j++)
                    table[h][j] = merge(table[h][j - 1], table[0][j]);
            }
        }
    }

    // O(N*logN)
    void buildSparseTable(const int a[]) {
        int blockN = 1;
        while (blockN < blockCount)
            blockN <<= 1;

        H.resize(max(blockN, blockSize));
        H[1] = 0;
        for (int i = 2; i < int(H.size()); i++)
            H[i] = H[i >> 1] + 1;

        //-- block sparse table - O(sqrt(N)*logN)
        blockSpTable.assign(H[blockN - 1] + 1, vector<int>(blockN, DEFAULT_VALUE));
        for (int i = 0; i < blockCount; i++)
            blockSpTable[0][i] = suffix[i * blockSize];

        buildSparseTable(blockSpTable);

        //-- sparse tables of blocks - O(N*logN)
        spTablesOfBlocks.assign(H[blockSize - 1] + 1, vector<int>(blockSize * blockCount, DEFAULT_VALUE));
        for (int i = 0; i < N; i++)
            spTablesOfBlocks[0][i] = a[i];

        buildSparseTable(spTablesOfBlocks);
    }


    // O(sqrt(N))
    void updatePrefixSuffix(int index) {
        int blockIndex = index / blockSize;

        int first = blockIndex * blockSize;
        int last = min(first + blockSize, N) - 1;

        prefix[index] = (index > first) ? merge(prefix[index - 1], spTablesOfBlocks[0][index])
                                        : spTablesOfBlocks[0][index];
        for (int j = index + 1; j <= last; j++)
            prefix[j] = merge(prefix[j - 1], spTablesOfBlocks[0][j]);

        suffix[index] = (index < last) ? merge(suffix[index + 1], spTablesOfBlocks[0][index])
                                       : spTablesOfBlocks[0][index];
        for (int j = index - 1; j >= first; j--)
            suffix[j] = merge(suffix[j + 1], spTablesOfBlocks[0][j]);
    }

    void updateSparseTable(vector<vector<int>>& table, int index) {
        for (int h = 1, range = 4; h < int(table.size()); h++, range <<= 1) {
            int half = range >> 1;
            int start = index & ~(range - 1);
            if ((index & half) == 0) { // suffix
                table[h][index] = (index + 1 < (start | half)) ? merge(table[h][index + 1], table[0][index])
                                                               : table[0][index];
                for (int i = index - 1; i >= start; i--)
                    table[h][i] = merge(table[h][i + 1], table[0][i]);
            } else { // prefix
                table[h][index] = (index > (start | half)) ? merge(table[h][index - 1], table[0][index])
                                                           : table[0][index];
                for (int i = index + 1, next = start + range; i < next; i++)
                    table[h][i] = merge(table[h][i - 1], table[0][i]);
            }
        }
    }

    // O(sqrt(N))
    void updateSparseTable(int index) {
        int blockIndex = index / blockSize;

        //-- block sparse table - O(sqrt(N))
        blockSpTable[0][blockIndex] = suffix[blockIndex * blockSize];
        updateSparseTable(blockSpTable, blockIndex);

        //-- sparse tables of blocks - O(sqrt(N))
        updateSparseTable(spTablesOfBlocks, index);
    }
};
