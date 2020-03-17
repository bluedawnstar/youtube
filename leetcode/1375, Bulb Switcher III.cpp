// https://leetcode.com/problems/bulb-switcher-iii/
// https://youtu.be/5wEKML_xnmA

// O(n)
class Solution {
public:
    int numTimesAllBlue(vector<int>& light) {
        int n = int(light.size());

        int last = 0;
        int count = 0;

        int res = 0;
        for (auto i : light) {
            count++;
            last = max(last, i);
            if (last == count)
                res++;
        }

        return res;
    }
};

