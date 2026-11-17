#include <gtest/gtest.h>
#include "../include/graph/undirected_graph.h"

TEST(IncidentIteratorTest, Traversal) {
    UndirectedGraph<int> g;
    Vertex<int> v1(1);
    Vertex<int> v2(2);
    Vertex<int> v3(3);
    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addEdge(v1, v2);
    g.addEdge(v1, v3);

    int count = 0;
    for (auto it = g.incidentBegin(v1); it != g.incidentEnd(v1); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}
