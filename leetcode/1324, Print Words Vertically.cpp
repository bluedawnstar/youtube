// https://leetcode.com/problems/maximum-69-number/
// https://www.youtube.com/watch?v=2548yA1Re78

class Solution {
public:
    vector<string> printVertically(string s) {
        vector<string> words;

        int maxLength = 0;

        string w;
        stringstream ss(s);
        while (ss >> w) {
            words.push_back(w);
            maxLength = max(maxLength, int(w.length()));
        }

        vector<string> result;
        for (int i = 0; i < maxLength; i++) {
            string temp;
            for (int j = 0; j < int(words.size()); j++) {
                if (words[j].length() <= i)
                    temp.push_back(' ');
                else
                    temp.push_back(words[j][i]);
            }

            // remove trailing spaces
            while (temp.back() == ' ')
                temp.pop_back();

            result.push_back(temp);
        }

        return result;
    }
};
