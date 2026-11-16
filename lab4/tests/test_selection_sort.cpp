#include <gtest/gtest.h>
#include "../include/sorting/selection_sort.h"
#include <vector>

TEST(SelectionSortTest, HandlesIntegers) {
    std::vector<int> v = {5, 2, 9, 1, 5, 6};
    selectionSort(v);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(SelectionSortTest, HandlesEmptyAndSingle) {
    std::vector<int> empty_v;
    selectionSort(empty_v);
    EXPECT_TRUE(empty_v.empty());

    std::vector<int> single_v = {42};
    selectionSort(single_v);
    EXPECT_EQ(single_v[0], 42);
}
