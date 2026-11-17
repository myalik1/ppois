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

TEST(UndirectedGraphTest, ExtendedOperationsAndExceptions) {
    UndirectedGraph<int> g;
    EXPECT_TRUE(g.empty());

    Vertex<int> v1(1);
    Vertex<int> v2(2);
    Vertex<int> v3(3);
    Vertex<int> v_missing(99);

    EXPECT_THROW(g.vertexDegree(v_missing), std::out_of_range);
    EXPECT_THROW(g.addEdge(v1, v2), std::out_of_range);
    EXPECT_THROW(g.incidentBegin(v_missing), std::out_of_range);
    EXPECT_THROW(g.adjacentBegin(v_missing), std::out_of_range);

    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addEdge(v1, v2, 2.0);
    g.addEdge(v2, v3, 3.0);

    Edge<int> existing_edge(v1, v2, 2.0);
    Edge<int> missing_edge(v1, v3, 1.0);
    EXPECT_EQ(g.edgeDegree(existing_edge), 1);
    EXPECT_THROW(g.edgeDegree(missing_edge), std::out_of_range);

    UndirectedGraph<int> g_copy(g);
    EXPECT_TRUE(g == g_copy);
    EXPECT_FALSE(g != g_copy);
    EXPECT_TRUE(g <= g_copy);
    EXPECT_TRUE(g >= g_copy);

    UndirectedGraph<int> g_smaller;
    g_smaller.addVertex(v1);
    EXPECT_TRUE(g_smaller < g);
    EXPECT_TRUE(g > g_smaller);

    std::ostringstream oss;
    oss << g;
    EXPECT_FALSE(oss.str().empty());

    auto edge_it = g.edgesBegin();
    g.removeEdge(edge_it);
    EXPECT_EQ(g.edgeCount(), 1);

    auto vert_it = g.begin();
    g.removeVertex(vert_it);
    EXPECT_EQ(g.vertexCount(), 2);

    g.clear();
    EXPECT_TRUE(g.empty());
}

TEST(UndirectedGraphTest, SameVertexCountComparisonAndIterators) {
    UndirectedGraph<int> g1;
    UndirectedGraph<int> g2;
    Vertex<int> v1(1), v2(2);

    g1.addVertex(v1);
    g1.addVertex(v2);
    g2.addVertex(v1);
    g2.addVertex(v2);
    g2.addEdge(v1, v2, 1.0);

    EXPECT_TRUE(g1 < g2);
    EXPECT_TRUE(g2 > g1);
    EXPECT_TRUE(g2.edgesCBegin() != g2.edgesCEnd());
    EXPECT_TRUE(g2.edgesRBegin() != g2.edgesREnd());
}
