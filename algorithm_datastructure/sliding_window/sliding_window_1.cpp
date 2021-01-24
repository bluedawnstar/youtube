// https://leetcode.com/discuss/interview-question/370112
// https://youtu.be/0uSEKnn5hJg

#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <iostream>

using namespace std;

// O(n*k) or O(n*k*logn)
vector<string> findUniqueSubstringsNaive(const string& s, int k) {
    int n = int(s.length());

    //unordered_set<string> strs;
    set<string> strs;
    for (int i = 0; i + k <= n; i++) {
        vector<bool> used(256);
        bool ok = true;
        for (int j = 0; j < k; j++) {
            if (used[s[i + j]]) {
                ok = false;
                break;
            }
            used[s[i + j]] = true;
        }

        if (ok)
            strs.insert(s.substr(i, k));
    }

    return vector<string>(strs.begin(), strs.end());
}

// O(n) or O(n*logn)
vector<string> findUniqueSubstrings(const string& s, int k) {
    int n = int(s.length());

    //unordered_set<string> strs;
    set<string> strs;

    vector<int> cnt(256);
    for (int L = 0, R = 0; R < n; R++) {
        // update right
        cnt[s[R]]++;

        // update left
        while (R - L + 1 > k || cnt[s[R]] > 1) {
            cnt[s[L++]]--;
        }

        // update answer
        if (R - L + 1 == k)
            strs.insert(s.substr(L, k));
    }

    return vector<string>(strs.begin(), strs.end());
}

bool check(vector<string> A, vector<string> B) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    return A == B;
}

int main() {
    cout << check(findUniqueSubstringsNaive("abcabc", 3), vector<string>{"abc", "bca", "cab"}) << endl;
    cout << check(findUniqueSubstringsNaive("abacab", 3), vector<string>{"bac", "cab"}) << endl;
    cout << check(findUniqueSubstringsNaive("awaglknagawunagwkwagl", 4),
                  vector<string>{"wagl", "aglk", "glkn", "lkna", "knag", "gawu", "awun", "wuna", "unag", "nagw", "agwk", "kwag"}) << endl;

    cout << check(findUniqueSubstrings("abcabc", 3), vector<string>{"abc", "bca", "cab"}) << endl;
    cout << check(findUniqueSubstrings("abacab", 3), vector<string>{"bac", "cab"}) << endl;
    cout << check(findUniqueSubstrings("awaglknagawunagwkwagl", 4),
                  vector<string>{"wagl", "aglk", "glkn", "lkna", "knag", "gawu", "awun", "wuna", "unag", "nagw", "agwk", "kwag"}) << endl;

    return 0;
}
