// https://leetcode.com/problems/tweet-counts-per-frequency/
// https://youtu.be/NO3r3k76S1o

// tree map, hash map
class TweetCounts {
public:
    // treeMap[time] = { hashMap[tweetName] = count }
    map<int, unordered_map<string, int>> M; // time -> { tweetName -> count, ... }

    TweetCounts() {

    }

    // O(logn)
    void recordTweet(string tweetName, int time) {
        M[time][tweetName]++;
    }

    // O(logn + t), t = endTime - startTime
    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        int interval;
        if (freq == "minute")
            interval = 60;
        else if (freq == "hour")
            interval = 60 * 60;
        else
            interval = 24 * 60 * 60;

        int startTimeInterval = startTime;
        int endTimeInterval = startTime + interval;

        vector<int> res;

        auto it = M.lower_bound(startTime);         // O(logn)
        while (startTimeInterval <= endTime) {
            int st = startTimeInterval;
            int et = min(endTimeInterval, endTime + 1);

            int cnt = 0;
            while (it != M.end() && st <= it->first && it->first < et) {
                auto itTweet = it->second.find(tweetName);
                if (itTweet != it->second.end())
                    cnt += itTweet->second;
                ++it;
            }
            res.push_back(cnt);

            startTimeInterval = endTimeInterval;
            endTimeInterval += interval;
        }

        return res;
    }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */
