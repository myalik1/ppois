#include <gtest/gtest.h>
#include "../include/graph/undirected_graph.h"

TEST(EdgeIteratorTest, Traversal) {
    UndirectedGraph<int> g;
    Vertex<int> v1(1);
    Vertex<int> v2(2);
    g.addVertex(v1);
    g.addVertex(v2);
    g.addEdge(v1, v2);

    int count = 0;
    for (auto it = g.edgesBegin(); it != g.edgesEnd(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 1);
}
