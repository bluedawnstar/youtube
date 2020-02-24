// https://leetcode.com/problems/largest-multiple-of-three/
// https://youtu.be/gktcR43XEe8

// method #1 : O(nlogn)
class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        int n = int(digits.size());

        vector<vector<int>> group(3);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += digits[i];
            group[digits[i] % 3].push_back(digits[i]);
        }
        sort(group[1].begin(), group[1].end(), greater<int>()); // descending order
        sort(group[2].begin(), group[2].end(), greater<int>()); // descending order

        if (sum % 3 == 1) {
            if (group[1].size() >= 1)
                group[1].pop_back();
            else if (group[2].size() >= 2)
                group[2].resize(group[2].size() - 2);
            else
                return "";
        } else if (sum % 3 == 2) {
            if (group[2].size() >= 1)
                group[2].pop_back();
            else if (group[1].size() >= 2)
                group[1].resize(group[1].size() - 2);
            else
                return "";
        }

        string res;
        for (auto x : group[0])
            res.push_back(x + '0');
        for (auto x : group[1])
            res.push_back(x + '0');
        for (auto x : group[2])
            res.push_back(x + '0');

        sort(res.begin(), res.end(), greater<char>());  // descending order
        if (res[0] == '0')
            res = "0";

        return res;
    }
};

// method #2 : O(n)
class Solution {
public:
    void subtract(vector<int>& count, int r, int n) {
        for (int i = r; i < 10 && n > 0; i += 3) {
            int d = min(count[i], n);
            count[i] -= d;
            n -= d;
        }
    }

    string largestMultipleOfThree(vector<int>& digits) {
        int n = int(digits.size());

        vector<int> count(10);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += digits[i];
            count[digits[i]]++;
        }

        if (sum % 3 == 1) {
            if (count[1] + count[4] + count[7] >= 1)
                subtract(count, 1, 1);
            else if (count[2] + count[5] + count[8] >= 2)
                subtract(count, 2, 2);
            else
                return "";
        } else if (sum % 3 == 2) {
            if (count[2] + count[5] + count[8] >= 1)
                subtract(count, 2, 1);
            else if (count[1] + count[4] + count[7] >= 2)
                subtract(count, 1, 2);
            else
                return "";
        }

        string res;
        for (int i = 9; i >= 0; i--) {
            while (count[i]-- > 0)
                res.push_back(i + '0');
        }
        if (res[0] == '0')
            res = "0";

        return res;
    }
};
