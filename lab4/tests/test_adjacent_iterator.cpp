#include <gtest/gtest.h>
#include "../include/graph/undirected_graph.h"

TEST(AdjacentIteratorTest, Traversal) {
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
    for (auto it = g.adjacentBegin(v1); it != g.adjacentEnd(v1); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST(AdjacentIteratorTest, ConstAndReverseTraversal) {
    UndirectedGraph<int> g;
    Vertex<int> v1(1), v2(2), v3(3);
    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addEdge(v1, v2);
    g.addEdge(v1, v3);

    const auto& cg = g;
    auto rit = cg.adjacentRBegin(v1);
    EXPECT_EQ(rit->getData(), 3);
    ++rit;
    EXPECT_EQ(rit->getData(), 2);
    ++rit;
    EXPECT_TRUE(rit == cg.adjacentREnd(v1));
}

TEST(AdjacentIteratorTest, ConstDirectOperators) {
    UndirectedGraph<int> g;
    Vertex<int> v1(1), v2(20), v3(30);
    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addEdge(v1, v2);
    g.addEdge(v1, v3);

    const auto& cg = g;
    auto cit = cg.adjacentBegin(v1);
    EXPECT_TRUE(cit != cg.adjacentEnd(v1));
    EXPECT_EQ(cit->getData(), 20);

    ++cit;
    EXPECT_EQ(cit->getData(), 30);

    const auto prev = cit--;
    EXPECT_EQ(prev->getData(), 30);
    EXPECT_EQ(cit->getData(), 20);

    const auto first = cit++;
    EXPECT_EQ(first->getData(), 20);
    EXPECT_EQ(cit->getData(), 30);
}
