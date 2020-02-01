#pragma once

struct WeightedGraph {
    const int INF = 0x3f3f3f3f;

    int N;
    vector<vector<pair<int, int>>> edges;

    void init(int n) {
        N = n;
        edges.resize(n);
    }

    void addEdge(int u, int v, int w) {
        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }

    //---

    vector<int> dist;
    vector<int> parent;

    // O(E*logV)
    void dijkstra(int start) {
        dist.assign(N, INF);
        parent.assign(N, -1);

        priority_queue<pair<int, int>> pq;   // (-weight, vertex)

        pq.emplace(0, start);
        dist[start] = 0;
        parent[start] = -1;
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
                    parent[v] = u;
                }
            }
        }
    }

    vector<int> getShortestPath(int v) const {
        vector<int> res;
        do {
            res.push_back(v);
            v = parent[v];
        } while (v >= 0);

        reverse(res.begin(), res.end());

        return res;
    }
};
