#include <gtest/gtest.h>
#include "../include/graph/undirected_graph.h"

TEST(VertexIteratorTest, Traversal) {
    UndirectedGraph<int> g;
    Vertex<int> v1(10);
    Vertex<int> v2(20);
    g.addVertex(v1);
    g.addVertex(v2);

    int count = 0;
    for (auto it = g.begin(); it != g.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}
