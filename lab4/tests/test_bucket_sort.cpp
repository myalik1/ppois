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
#include "../include/sorting/student_record.h"

TEST(BucketSortTest, HandlesRawArraysAndCustomObjects) {
    double raw_arr[] = {0.82, 0.14, 0.65, 0.31};
    bucketSort(raw_arr, 4);
    EXPECT_TRUE(std::is_sorted(raw_arr, raw_arr + 4));

    std::vector<StudentRecord> students = {{"Oleg", 8.0}, {"Maria", 9.8}, {"Dmitry", 5.4}};
    bucketSort(students);
    EXPECT_EQ(students[0].getName(), "Dmitry");
    EXPECT_EQ(students[2].getName(), "Maria");
}
