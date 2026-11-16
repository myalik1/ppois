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
