// https://leetcode.com/problems/subsets-ii/
// https://youtu.be/kaIZnfwYg1M

// method #1 : backtracking & erase, O(n^2 * 2^n)
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

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = int(nums.size());
        vector<vector<int>> res;
        vector<int> v;
        rec(res, nums, v, 0);

        sort(res.begin(), res.end());
        res.erase(unique(res.begin(), res.end()), res.end());

        return res;
    }
};

// method #2 : backtracking, O(n*2^n)
class Solution {
public:
    void rec(vector<vector<int>>& res, const vector<int>& nums, vector<int>& v, int depth) {
        res.push_back(v);
        for (int i = depth; i < int(nums.size()); i++) {
            if (i != depth && nums[i - 1] == nums[i])
                continue;
            v.push_back(nums[i]);
            rec(res, nums, v, i + 1);
            v.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = int(nums.size());
        vector<vector<int>> res;
        vector<int> v;
        rec(res, nums, v, 0);

        return res;
    }
};
