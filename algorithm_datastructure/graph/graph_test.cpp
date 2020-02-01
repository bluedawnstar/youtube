#include <vector>
#include <queue>
#include <iostream>

using namespace std;

#include "graph.h"
#include "graph_weighted.h"
#include "graph_weighted_all_path.h"

void test_graph() {
    UndirectedGraph graph;
    graph.init(5);

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    //graph.iterateDFS(0);
    graph.iterateBFS(0);
}
