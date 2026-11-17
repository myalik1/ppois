#include <gtest/gtest.h>
#include "../include/graph/vertex.h"

TEST(VertexTest, CreationAndComparison) {
    Vertex<int> v1(10);
    Vertex<int> v2(20);
    EXPECT_EQ(v1.getData(), 10);
    v1.setData(15);
    EXPECT_EQ(v1.getData(), 15);
    EXPECT_NE(v1, v2);
}

TEST(VertexTest, IdAndComparisonOperators) {
    Vertex<int> v1(10);
    Vertex<int> v2(20);
    EXPECT_LT(v1.getId(), v2.getId());
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v2 > v1);
    EXPECT_TRUE(v1 <= v2);
    EXPECT_TRUE(v2 >= v1);
}
