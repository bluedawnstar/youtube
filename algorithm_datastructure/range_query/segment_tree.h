#pragma once

struct SegmentTree {
    int N;              // size
    vector<int> tree;   // segment tree

    // merge operation
    int merge(int left, int right) {
        return left + right;        // sum
        //return min(left, right);  // min
        //return max(left, right);  // max
        //...
    }


    void build(const int arr[], int size) {
        N = size;
        tree.resize(N * 4);

        buildRec(arr, 1, 0, N - 1);
    }

    // inclusive
    int update(int index, int newValue) {
        return updateRec(index, newValue, 1, 0, N - 1);
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
    int buildRec(const int arr[], int node, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight)
            return tree[node] = arr[nodeLeft];

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        int leftVal  = buildRec(arr, node * 2    , nodeLeft, mid);
        int rightVal = buildRec(arr, node * 2 + 1, mid + 1, nodeRight);
        return tree[node] = merge(leftVal, rightVal);
    }

    int updateRec(int index, int newValue, int node, int nodeLeft, int nodeRight) {
        if (index < nodeLeft || nodeRight < index)
            return tree[node];

        if (nodeLeft == nodeRight)
            return tree[node] = newValue;

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        int leftVal  = updateRec(index, newValue, node * 2    , nodeLeft, mid);
        int rightVal = updateRec(index, newValue, node * 2 + 1, mid + 1, nodeRight);
        return tree[node] = merge(leftVal, rightVal);
    }

    int updateRec(int left, int right, int newValue, int node, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || nodeRight < left)
            return tree[node];

        if (nodeLeft == nodeRight)
            return tree[node] = newValue;

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        int leftVal  = updateRec(left, right, newValue, node * 2    , nodeLeft, mid);
        int rightVal = updateRec(left, right, newValue, node * 2 + 1, mid + 1, nodeRight);
        return tree[node] = merge(leftVal, rightVal);
    }

    int queryRec(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (right < nodeLeft || nodeRight < left)
            return 0;           // default value

        if (left <= nodeLeft && nodeRight <= right)
            return tree[node];

        int mid = nodeLeft + (nodeRight - nodeLeft) / 2;
        return merge(queryRec(left, right, node * 2    , nodeLeft, mid),
                     queryRec(left, right, node * 2 + 1, mid + 1, nodeRight));
    }
};
