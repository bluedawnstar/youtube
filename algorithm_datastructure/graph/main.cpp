#include <vector>
#include <queue>
#include <iostream>

using namespace std;

#include "graph.h"
#include "graph_weighted.h"
#include "graph_weighted_all_path.h"

void testBasicGraph_1() {
    cout << "* Basic graph - DFS traversal" << endl;

    const int N = 5;

    Graph graph;
    graph.init(N);

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    graph.traverseDFS(0);

    cout << endl;
}

void testBasicGraph_2() {
    cout << "* Basic graph - BFS traversal" << endl;

    const int N = 5;

    Graph graph;
    graph.init(N);

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    graph.traverseBFS(0);

    cout << endl;
}

void testBasicGraph_3() {
    cout << "* Basic graph - shortest path (without weight)" << endl;

    const int N = 9;

    Graph graph;
    graph.init(N);

    graph.addDirectedEdge(0, 1);
    graph.addDirectedEdge(0, 7);
    graph.addDirectedEdge(1, 2);
    graph.addDirectedEdge(1, 7);
    graph.addDirectedEdge(2, 5);
    graph.addDirectedEdge(3, 2);
    graph.addDirectedEdge(4, 3);
    graph.addDirectedEdge(5, 4);
    graph.addDirectedEdge(6, 5);
    graph.addDirectedEdge(7, 6);
    graph.addDirectedEdge(7, 8);
    graph.addDirectedEdge(8, 2);
    graph.addDirectedEdge(8, 6);

    graph.shortestPath(0);

    cout << "distance : ";
    for (int i = 0; i < N; i++) {
        cout << graph.dist[i] << ", ";
    }
    cout << endl << endl;
}


void testDijkstra() {
    cout << "* Dijkstra" << endl;

    const int N = 9;

    WeightedGraph graph;
    graph.init(N);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 7, 8);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 7, 11);
    graph.addEdge(2, 3, 7);
    graph.addEdge(2, 5, 4);
    graph.addEdge(2, 8, 2);
    graph.addEdge(3, 4, 9);
    graph.addEdge(3, 5, 14);
    graph.addEdge(4, 5, 10);
    graph.addEdge(5, 6, 2);
    graph.addEdge(6, 7, 1);
    graph.addEdge(6, 8, 6);
    graph.addEdge(7, 8, 7);

    graph.dijkstra(0);

    cout << "distance : ";
    for (int i = 0; i < N; i++) {
        cout << graph.dist[i] << ", ";
    }
    cout << endl << endl;
}


void testFloydWarshall() {
    cout << "* Floyd-Warshall" << endl;

    const int N = 4;

    WeightedGraphAllPath graph;
    graph.init(N);

    graph.addDirectedEdge(0, 1, -5);
    graph.addDirectedEdge(0, 2, 2);
    graph.addDirectedEdge(1, 2, 4);
    graph.addDirectedEdge(2, 3, 1);
    graph.addDirectedEdge(3, 0, 3);

    graph.floydWarshall();

    cout << "distance : " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int d = graph.dist[i][j];
            if (d >= graph.INF)
                cout << "INF" << ", ";
            else
                cout << d << ", ";
        }
        cout << endl;
    }
    cout << endl;
}


int main(void) {
    testBasicGraph_1();
    testBasicGraph_2();
    testBasicGraph_3();

    testDijkstra();

    testFloydWarshall();

    return 0;
}
