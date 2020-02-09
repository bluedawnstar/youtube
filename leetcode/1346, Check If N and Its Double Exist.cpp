// https://leetcode.com/problems/check-if-n-and-its-double-exist/
// https://youtu.be/_qxTzgOwKpc

// map, O(n)
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        int n = int(arr.size());
        unordered_set<int> S;   // hash set
        for (int i = 0; i < n; i++) {
            if (S.find(arr[i] * 2) != S.end())
                return true;
            if (arr[i] % 2 == 0 && S.find(arr[i] / 2) != S.end())
                return true;
            S.insert(arr[i]);
        }
        return false;
    }
};
