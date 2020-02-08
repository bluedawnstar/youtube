// https://leetcode.com/problems/reduce-array-size-to-the-half/
// https://youtu.be/tXLNOkOAVQY

// O(nlogn)
class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int n = int(arr.size());

        unordered_map<int, int> M;
        for (int x : arr)
            ++M[x];

        vector<pair<int, int>> v;   // (count, x)
        for (auto it : M)
            v.emplace_back(it.second, it.first);
        sort(v.begin(), v.end(), greater<pair<int, int>>());

        int cnt = 0;
        int res = 0;
        for (int i = 0; i < int(v.size()); i++) {
            cnt += v[i].first;
            ++res;
            if (cnt >= (n + 1) / 2)
                break;
        }

        return res;
    }
};
