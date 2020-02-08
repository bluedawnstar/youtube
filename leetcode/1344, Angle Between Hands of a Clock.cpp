// https://leetcode.com/problems/angle-between-hands-of-a-clock/
// https://youtu.be/S4XKV2mrpXM

// O(1)
class Solution {
public:
    double angleClock(int hour, int minutes) {
        int totalMinutes = hour * 60 + minutes;

        double angleHour = 360.0 * totalMinutes / (60.0 * 12);
        double angleMinute = 360.0 * minutes / 60.0;

        double res = abs(angleHour - angleMinute);
        if (res > 180.0)
            res = 360.0 - res;

        return res;
    }
};
