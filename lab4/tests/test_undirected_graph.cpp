#include <gtest/gtest.h>
#include "../include/graph/undirected_graph.h"

TEST(UndirectedGraphTest, BasicOperations) {
    UndirectedGraph<int> g;
    Vertex<int> v1(1);
    Vertex<int> v2(2);
    Vertex<int> v3(3);

    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);

    EXPECT_EQ(g.vertexCount(), 3);
    EXPECT_TRUE(g.hasVertex(v1));

    g.addEdge(v1, v2, 1.0);
    g.addEdge(v2, v3, 2.0);

    EXPECT_EQ(g.edgeCount(), 2);
    EXPECT_TRUE(g.hasEdge(v1, v2));
    EXPECT_EQ(g.vertexDegree(v2), 2);

    g.removeEdge(v1, v2);
    EXPECT_FALSE(g.hasEdge(v1, v2));
    EXPECT_EQ(g.edgeCount(), 1);

    g.removeVertex(v3);
    EXPECT_EQ(g.vertexCount(), 2);
    EXPECT_FALSE(g.hasVertex(v3));
}
