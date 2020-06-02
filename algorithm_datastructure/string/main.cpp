#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "string_matching.h"

void test_matching() {
    const string s = "AABAACAADAABAABA";
    const string t = "AABA";

    vector<int> ans_naive = searchNaive(s, t);
    vector<int> ans_kmp = kmp(s, t);

    if (ans_naive != ans_kmp)
        cout << "ERROR: mismatch! : s = " << s << ", t = " << t << endl;
    else
        cout << "OK" << endl;
}

int main(void) {
    test_matching();

    return 0;
}
