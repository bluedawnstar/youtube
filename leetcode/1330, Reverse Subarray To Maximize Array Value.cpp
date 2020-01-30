// https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/
// https://youtu.be/8Au3xuwHfTM

// method #1 : brute force, O(n^2)
class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = int(nums.size());
        int sum = 0;
        for (int i = 1; i < n; i++)
            sum += abs(nums[i] - nums[i - 1]);

        int result = sum;
        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right < n; right++) {
                int delta = 0;
                if (left > 0) {
                    delta -= abs(nums[left] - nums[left - 1]);
                    delta += abs(nums[right] - nums[left - 1]);
                }
                if (right + 1 < n) {
                    delta -= abs(nums[right + 1] - nums[right]);
                    delta += abs(nums[right + 1] - nums[left]);
                }
                result = max(result, sum + delta);
            }
        }
        return result;
    }
};

// method #2 : optimal solution, O(n)
class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = int(nums.size());
        if (n <= 1)
            return 0;

        int sum = 0;

        int minX = 1000000000;  //numeric_limits<int>::max();
        int maxX = -1000000000;  //numeric_limits<int>::min();
        int minPos = 0;
        int maxPos = 0;
        for (int i = 1; i < n; i++) {
            int currMinX = min(nums[i], nums[i - 1]);
            int currMaxX = max(nums[i], nums[i - 1]);
            sum += currMaxX - currMinX;

            if (currMaxX < minX) {
                minX = currMaxX;
                minPos = i;
            }
            if (currMinX > maxX) {
                maxX = currMinX;
                maxPos = i;
            }
        }

        int result = sum;
        result = max(result, sum + (maxX - minX) * 2);
        result = max(result, sum - abs(nums[maxPos] - nums[maxPos - 1]) + abs(nums[maxPos] - nums[0]));
        result = max(result, sum - abs(nums[minPos] - nums[minPos - 1]) + abs(nums[minPos] - nums[0]));
        result = max(result, sum - abs(nums[maxPos] - nums[maxPos - 1]) + abs(nums[maxPos - 1] - nums[n - 1]));
        result = max(result, sum - abs(nums[minPos] - nums[minPos - 1]) + abs(nums[minPos - 1] - nums[n - 1]));

        return result;
    }
};
