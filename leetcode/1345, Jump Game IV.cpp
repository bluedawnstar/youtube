// https://leetcode.com/problems/jump-game-iv/
// https://youtu.be/S4XKV2mrpXM

// BFS, O(n)
class Solution {
public:
    int minJumps(vector<int>& arr) {
        const int INF = 0x3f3f3f3f;

        int n = int(arr.size());
        if (n <= 1)
            return 0;

        unordered_set<int> S;                   // hash set
        unordered_map<int, vector<int>> M;      // hash map
        for (int i = 0; i < n; i++)
            M[arr[i]].push_back(i);

        vector<int> dist(n, INF);
        dist[0] = 0;

        queue<pair<int, int>> Q;                // (index, distance)
        Q.emplace(0, 0);
        while (!Q.empty() && dist[n - 1] == INF) {
            int idx, d;
            tie(idx, d) = Q.front();
            Q.pop();

            if (S.find(arr[idx]) == S.end()) {  // not exist in S
                for (int i : M[arr[idx]]) {
                    if (dist[i] != INF)
                        continue;
                    dist[i] = d + 1;
                    Q.emplace(i, d + 1);
                }
                S.insert(arr[idx]);
            }

            if (idx > 0 && dist[idx - 1] == INF) {
                dist[idx - 1] = d + 1;
                Q.emplace(idx - 1, d + 1);
            }

            if (idx + 1 < n && dist[idx + 1] == INF) {
                dist[idx + 1] = d + 1;
                Q.emplace(idx + 1, d + 1);
            }
        }

        return dist[n - 1];
    }
};
