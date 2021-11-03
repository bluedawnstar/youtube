#pragma once

struct SegmentTreeLazy {
    static const int DEFAULT_VALUE = 0;
    //static const int DEFAULT_VALUE = numeric_limits<int>::max(); // for min
    //static const int DEFAULT_VALUE = numeric_limits<int>::min(); // for max

    int merge(int left, int right) {
        return left + right; // sum
        //return min(left, right); // min
        //return max(left, right); // max
    }

    int mergeBlock(int value, int size) {
        return value * size;    // sum
        //return value;         // min
        //return value;         // max
    }


    int N;                  // size
    vector<int> tree;       // segment tree
    vector<int> lazyValue;  // lazy value
    vector<bool> lazyExist; // 

    void build(const int arr[], int size) {
        N = size;
        tree.resize(N * 4);
        lazyValue.assign(N * 4, DEFAULT_VALUE);
        lazyExist.assign(N * 4, false);

        buildRec(arr, 1, 0, N - 1);
    }

    // inclusive
    int update(int left, int right, int newValue) {
        return updateRec(left, right, newValue, 1, 0, N - 1);
    }

    // inclusive
    int query(int left, int right) {
        return queryRec(left, right, 1, 0, N - 1);
    }

private:
    int pushDown(int newValue, int node, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight)
            return tree[node] = newValue;

        lazyExist[node] = true;
        lazyValue[node] = newValue;
        return tree[node] = mergeBlock(newValue, nodeRight - nodeLeft + 1);
    }

    int buildRec(const int arr[], int node, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight)
            return tree[node] = arr[nodeLeft];

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        int leftVal = buildRec(arr, node * 2, nodeLeft, mid);
        int rightVal = buildRec(arr, node * 2 + 1, mid + 1, nodeRight);
        return tree[node] = merge(leftVal, rightVal);
    }

    int updateRec(int left, int right, int newValue, int node, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || nodeRight < left)
            return tree[node];

        if (nodeLeft == nodeRight)
            return tree[node] = newValue;

        if (left <= nodeLeft && nodeRight <= right) {
            lazyExist[node] = true;
            lazyValue[node] = newValue;
            return tree[node] = mergeBlock(newValue, nodeRight - nodeLeft + 1);
        }

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (lazyExist[node]) {
            lazyExist[node] = false;
            pushDown(lazyValue[node], node * 2, nodeLeft, mid);
            pushDown(lazyValue[node], node * 2 + 1, mid + 1, nodeRight);
            lazyValue[node] = DEFAULT_VALUE;
        }

        int leftVal = updateRec(left, right, newValue, node * 2, nodeLeft, mid);
        int rightVal = updateRec(left, right, newValue, node * 2 + 1, mid + 1, nodeRight);
        return tree[node] = merge(leftVal, rightVal);
    }

    int queryRec(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || nodeRight < left)
            return DEFAULT_VALUE;           // default value

        if (left <= nodeLeft && nodeRight <= right)
            return tree[node];

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        if (lazyExist[node]) {
            lazyExist[node] = false;
            pushDown(lazyValue[node], node * 2, nodeLeft, mid);
            pushDown(lazyValue[node], node * 2 + 1, mid + 1, nodeRight);
            lazyValue[node] = DEFAULT_VALUE;
        }

        return merge(queryRec(left, right, node * 2, nodeLeft, mid),
                     queryRec(left, right, node * 2 + 1, mid + 1, nodeRight));
    }
};
