#include <gtest/gtest.h>
#include "../include/sorting/bucket_sort.h"
#include <vector>

TEST(BucketSortTest, HandlesDoubles) {
    std::vector<double> v = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21};
    bucketSort(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(BucketSortTest, HandlesEmpty) {
    std::vector<double> v;
    bucketSort(v);
    EXPECT_TRUE(v.empty());
}
