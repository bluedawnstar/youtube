#pragma once

struct Graph {
    int N;
    vector<vector<int>> edges;

    void init(int n) {
        N = n;
        edges.resize(n);
    }

    void addEdge(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void addDirectedEdge(int u, int v) {
        edges[u].push_back(v);
    }

    //--- DFS

    void dfs(vector<bool>& visited, int u) {
        //贸府 内靛ˇ
        cout << "visit : " << u << endl;

        visited[u] = true;
        for (int v : edges[u]) {
            if (!visited[v])
                dfs(visited, v);
        }
    }

    void traverseDFS(int start) {
        vector<bool> visited(N);
        dfs(visited, start);
    }

    //--- BFS

    void traverseBFS(int start) {
        vector<bool> visited(N);

        queue<int> Q;
        Q.push(start);
        visited[start] = true;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            // 贸府 内靛ˇ
            cout << "visit : " << u << endl;

            for (int v : edges[u]) {
                if (visited[v])
                    continue;

                visited[v] = true;
                Q.push(v);
            }
        }

    }

    //--- 
    
    bool isCyclicUndirectedGraph(vector<bool>& visited, int u, int parent) const {
        visited[u] = true;
        for (int v : edges[u]) {
            if (!visited[v]) {
                if (isCyclicUndirectedGraph(visited, v, u))
                    return true;
            } else if (v != parent)
                return true;
        }

        return false;
    }

    bool isCyclicUndirectedGraph(int start) const {
        vector<bool> visited(N);
        return isCyclicUndirectedGraph(visited, start, -1);
    }

    //--- 

    bool isCyclicDirectedGraph(vector<bool>& visited, vector<bool>& visitStack, int u) const {
        visited[u] = true;
        visitStack[u] = true;
        for (int v : edges[u]) {
            if (!visited[v]) {
                if (isCyclicDirectedGraph(visited, visitStack, v))
                    return true;
            } else if (visitStack[v])
                return true;
        }
        visitStack[u] = false;
        return false;
    }

    bool isCyclicDirectedGraph(int start) const {
        vector<bool> visited(N);
        vector<bool> visitStack(N);
        return isCyclicDirectedGraph(visited, visitStack, start);
    }

    //---

    vector<int> dist;
    vector<int> parent;

    // O(E)
    void shortestPath(int start) {
        dist.assign(N, -1);
        parent.assign(N, -1);

        queue<int> Q;

        Q.push(start);
        dist[start] = 0;
        parent[start] = -1;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            for (int v : edges[u]) {
                if (dist[v] < 0) {
                    Q.push(v);
                    dist[v] = dist[u] + 1;
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
