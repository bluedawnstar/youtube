// https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/
// https://youtu.be/AKWegRq_jY0

// O(n)
class Solution {
public:
    int char2idx(char c) {
        switch (c) {
        case 'a': return 0;
        case 'e': return 1;
        case 'i': return 2;
        case 'o': return 3;
        case 'u': return 4;
        }
        return -1;
    }

    int findTheLongestSubstring(string s) {
        vector<int> first(32, -2);

        int res = 0;

        int curr = 0;
        first[curr] = -1;
        for (int i = 0; i < int(s.length()); i++) {
            int idx = char2idx(s[i]);
            if (idx >= 0)
                curr ^= (1 << idx);

            if (first[curr] >= -1)
                res = max(res, i - first[curr]);
            else
                first[curr] = i;
        }

        return res;
    }
};

// O(n), with hash map
class Solution {
public:
    int char2idx(char c) {
        switch (c) {
        case 'a': return 0;
        case 'e': return 1;
        case 'i': return 2;
        case 'o': return 3;
        case 'u': return 4;
        }
        return -1;
    }

    int findTheLongestSubstring(string s) {
        unordered_map<int, int> first;

        int res = 0;

        int curr = 0;
        first[curr] = -1;
        for (int i = 0; i < int(s.length()); i++) {
            int idx = char2idx(s[i]);
            if (idx >= 0)
                curr ^= (1 << idx);

            if (first.find(curr) != first.end())
                res = max(res, i - first[curr]);
            else
                first[curr] = i;
        }

        return res;
    }
};
