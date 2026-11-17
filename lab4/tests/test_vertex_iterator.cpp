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

TEST(VertexIteratorTest, ConstAndReverseTraversal) {
    UndirectedGraph<int> g;
    Vertex<int> v1(10);
    Vertex<int> v2(20);
    g.addVertex(v1);
    g.addVertex(v2);

    const auto& cg = g;
    auto cit = cg.begin();
    EXPECT_EQ(cit->getData(), 10);
    EXPECT_EQ((*cit).getData(), 10);
    ++cit;
    EXPECT_EQ(cit->getData(), 20);
    --cit;
    EXPECT_TRUE(cit == cg.begin());
    EXPECT_NE(cit, cg.end());

    int rev_sum = 0;
    for (auto rit = g.rbegin(); rit != g.rend(); ++rit) {
        rev_sum += rit->getData();
    }
    EXPECT_EQ(rev_sum, 30);
}
