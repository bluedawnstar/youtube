// https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/
// https://youtu.be/4BqoDLdGDaE

// O(n*m*log(n*m))
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int N = int(grid.size());
        int M = int(grid[0].size());

        const int dydx[][2] = {
            {  0,  1 }, // right (1)
            {  0, -1 }, // left (2)
            {  1,  0 }, // down (3)
            { -1,  0 }, // up (4)
        };

        const int INF = 0x3f3f3f3f;
        vector<vector<int>> dist(N, vector<int>(M, INF));

        priority_queue<tuple<int, int, int>> pq;// (-cost, row, col)

        pq.emplace(0, 0, 0);
        dist[0][0] = 0;

        int d, row, col;
        while (!pq.empty()) {
            tie(d, row, col) = pq.top();
            d = -d;
            pq.pop();

            if (dist[row][col] < d)
                continue;

            for (int i = 0; i < 4; i++) {
                int r = row + dydx[i][0];
                int c = col + dydx[i][1];
                if (r < 0 || r >= N || c < 0 || c >= M)
                    continue;

                int d2;
                if (grid[row][col] == i + 1)    // right=1, left=2, down=3, up=4
                    d2 = d;
                else
                    d2 = d + 1;

                if (dist[r][c] > d2) {
                    pq.emplace(-d2, r, c);
                    dist[r][c] = d2;
                }
            }
        }

        return dist[N - 1][M - 1];
    }
};
