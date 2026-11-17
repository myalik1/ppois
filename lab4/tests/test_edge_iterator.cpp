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

TEST(EdgeIteratorTest, ConstAndBidirectionalOps) {
    UndirectedGraph<int> g;
    Vertex<int> v1(1);
    Vertex<int> v2(2);
    Vertex<int> v3(3);
    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addEdge(v1, v2, 1.5);
    g.addEdge(v2, v3, 2.5);

    const auto& cg = g;
    auto cit = cg.edgesBegin();
    EXPECT_DOUBLE_EQ(cit->getWeight(), 1.5);
    EXPECT_DOUBLE_EQ((*cit).getWeight(), 1.5);
    ++cit;
    EXPECT_DOUBLE_EQ(cit->getWeight(), 2.5);
    --cit;
    EXPECT_TRUE(cit == cg.edgesBegin());
    EXPECT_NE(cit, cg.edgesEnd());
}
