#pragma once

struct WeightedGraphAllPath {
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

    void addDirectedEdge(int u, int v, int w) {
        edges[u].emplace_back(v, w);
    }

    //---

    vector<vector<int>> dist;
    vector<vector<int>> parent;

    // O(V^3)
    void floydWarshall() {
        dist.assign(N, vector<int>(N, INF));
        parent.assign(N, vector<int>(N, -1));

        for (int i = 0; i < N; i++) {
            dist[i][i] = 0;
            for (auto& e : edges[i]) {
                dist[i][e.first] = e.second;
                parent[i][e.first] = i;
            }
        }

        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        parent[i][j] = parent[k][j];
                    }
                }
            }
        }
    }

    vector<int> getPath(int u, int v) {
        vector<int> res;
        res.reserve(N);

        while (true) {
            res.push_back(v);
            if (u == v)
                break;
            v = parent[u][v];
        }

        reverse(res.begin(), res.end());

        return res;
    }
};
