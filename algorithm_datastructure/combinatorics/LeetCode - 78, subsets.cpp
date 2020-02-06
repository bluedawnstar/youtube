// https://leetcode.com/problems/subsets/
// https://youtu.be/wy678Yc5iqE

// method #1 : using bitset, O(n*2^n)
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = int(nums.size());

        vector<vector<int>> res;
        for (int i = 0; i < (1 << n); i++) {
            vector<int> v;
            for (int j = 0, t = i; t; j++, t >>= 1) {
                if (t & 1)
                    v.push_back(nums[j]);
            }
            res.push_back(v);
        }

        return res;
    }
};

// method #2 : backtracking, O(n*2^n)
class Solution {
public:
    void rec(vector<vector<int>>& res, const vector<int>& nums, vector<int>& v, int depth) {
        if (depth >= nums.size()) {
            res.push_back(v);
            return;
        }

        // exclude nums[depth]
        rec(res, nums, v, depth + 1);

        // include nums[depth]
        v.push_back(nums[depth]);
        rec(res, nums, v, depth + 1);
        v.pop_back();
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        int n = int(nums.size());
        vector<vector<int>> res;
        vector<int> v;
        rec(res, nums, v, 0);
        return res;
    }
};

// method #3 : enhanced backtracking, O(n*2^n)
class Solution {
public:
    void rec(vector<vector<int>>& res, const vector<int>& nums, vector<int>& v, int depth) {
        res.push_back(v);
        for (int i = depth; i < int(nums.size()); i++) {
            v.push_back(nums[i]);
            rec(res, nums, v, i + 1);
            v.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        int n = int(nums.size());
        vector<vector<int>> res;
        vector<int> v;
        rec(res, nums, v, 0);
        return res;
    }
};
