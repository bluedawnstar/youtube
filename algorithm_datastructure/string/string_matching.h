#pragma once

inline vector<int> searchNaive(const string& text, const string& pattern) {
    vector<int> res;

    int textLength = (int)text.length();
    int patternLength = (int)pattern.length();

    for (int i = 0; i <= textLength - patternLength; i++) {
        bool matched = true;
        for (int j = 0; j < patternLength; j++) {
            if (text[i + j] != pattern[j]) {
                matched = false;
                break;
            }
        }

        if (matched)
            res.push_back(i);
    }

    return res;
}

//--- kmp

// O(m)
inline vector<int> prefixFunction(const string& s) {
    int n = int(s.length());
    vector<int> pi(n);

    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && s[j] != s[i])
            j = pi[j - 1];

        if (s[j] == s[i])
            j++;

        pi[i] = j;
    }
    return pi;
}

// O(n + m)
inline vector<int> kmp(const string& s, const string& t) {
    int n = int(s.length());
    int m = int(t.length());

    vector<int> res;
    vector<int> pi = prefixFunction(t);

    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && s[i] != t[j])
            j = pi[j - 1];

        if (s[i] == t[j]) {
            if (j == m - 1) {
                res.push_back(i - m + 1);
                j = pi[j];
            } else {
                j++;
            }
        }
    }
    return res;
}
