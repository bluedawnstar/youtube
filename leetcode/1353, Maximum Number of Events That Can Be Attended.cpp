// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
// https://youtu.be/5zr_G17sxBU

// O(nlogn)
class Solution {
public:
    // events = { (start, end), ... }
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());

        int lastDay = 0;
        for (auto& e : events)
            lastDay = max(lastDay, e[1]);

        int result = 0;
        priority_queue<int> Q;  // min heap
        for (int i = 0, currDay = 1; currDay <= lastDay; currDay++) {
            // add new candidates
            while (i < int(events.size()) && currDay == events[i][0]) {
                Q.push(-events[i][1]);
                i++;
            }
            // remove out-of-date candidates
            while (!Q.empty() && -Q.top() < currDay)
                Q.pop();
            // select a candidate
            if (!Q.empty()) {
                Q.pop();
                result++;
            }
        }
        return result;
    }
};
