#include <gtest/gtest.h>
#include "../include/graph/edge.h"
#include "../include/graph/vertex.h"

TEST(EdgeTest, CreationAndWeights) {
    Vertex<int> v1(1);
    Vertex<int> v2(2);
    Edge<int> e(v1, v2, 3.5);
    EXPECT_EQ(e.getWeight(), 3.5);
    e.setWeight(5.0);
    EXPECT_EQ(e.getWeight(), 5.0);

    Edge<int> e_rev(v2, v1, 5.0);
    EXPECT_EQ(e, e_rev);
}
