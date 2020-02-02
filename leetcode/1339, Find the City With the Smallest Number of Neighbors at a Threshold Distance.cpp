// https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
// https://youtu.be/lPYYWlRDF-A

struct Graph {
    const int INF = 0x3f3f3f3f;

    int n;
    // adjacency list
    vector<vector<pair<int, int>>> edges;    // (vertex, weight)

    void init(int n) {
        this->n = n;
        edges.resize(n);
    }

    void addEdge(int u, int v, int weight) {
        edges[u].emplace_back(v, weight);
        edges[v].emplace_back(u, weight);
    }

    // O(V^3)
    vector<vector<int>> floydWarshall() {
        vector<vector<int>> dist(n, vector<int>(n, INF));

        // initialize
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
            for (auto& e : edges[i])
                dist[i][e.first] = e.second;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        return dist;
    }

    // O(E*logV)
    vector<int> dijkstra(int start) {
        vector<int> dist(n, INF);

        priority_queue<pair<int, int>> pq;   // (-weight, vertex)
        pq.emplace(0, start);
        dist[start] = 0;

        while (!pq.empty()) {
            int w = -pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (dist[u] < w)
                continue;

            for (auto& e : edges[u]) {
                int v = e.first;
                int vw = w + e.second;
                if (dist[v] > vw) {
                    pq.emplace(-vw, v);
                    dist[v] = vw;
                }
            }
        }

        return dist;
    }
};

// method #1 : O(V^3)
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        Graph graph;
        graph.init(n);

        for (auto& ev : edges)
            graph.addEdge(ev[0], ev[1], ev[2]);

        auto dist = graph.floydWarshall();

        int ans = 0;                // vertex number
        int ansReachableCount = n;

        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && dist[i][j] <= distanceThreshold)
                    cnt++;
            }

            if (cnt <= ansReachableCount) {
                ans = i;
                ansReachableCount = cnt;
            }
        }

        return ans;
    }
};

// method #2 : O(VE*logV)
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        Graph graph;
        graph.init(n);

        for (auto& ev : edges)
            graph.addEdge(ev[0], ev[1], ev[2]);

        int ans = 0;                        // vertex number
        int ansReachableCount = n;

        for (int i = 0; i < n; i++) {
            auto dist = graph.dijkstra(i);  // O(E*logV)

            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && dist[j] <= distanceThreshold)
                    cnt++;
            }

            if (cnt <= ansReachableCount) {
                ans = i;
                ansReachableCount = cnt;
            }
        }

        return ans;
    }
};
