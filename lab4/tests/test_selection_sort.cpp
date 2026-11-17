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
#include "../include/sorting/student_record.h"

TEST(SelectionSortTest, HandlesRawArraysAndCustomObjects) {
    int raw_arr[] = {9, 3, 7, 1, 5};
    selectionSort(raw_arr, 5);
    EXPECT_TRUE(std::is_sorted(raw_arr, raw_arr + 5));

    StudentRecord students[] = {{"Boris", 7.2}, {"Anna", 9.5}, {"Ivan", 6.1}};
    selectionSort(students);
    EXPECT_EQ(students[0].getName(), "Ivan");
    EXPECT_EQ(students[2].getName(), "Anna");
}

TEST(StudentRecordTest, EqualityTieBreakAndStreamOutput) {
    StudentRecord s1("Anna", 8.5);
    StudentRecord s2("Boris", 8.5);
    StudentRecord s3("Anna", 8.5);

    EXPECT_TRUE(s1 < s2);
    EXPECT_TRUE(s1 == s3);
    EXPECT_TRUE(s1 != s2);

    std::ostringstream oss;
    oss << s1;
    EXPECT_EQ(oss.str(), "Anna (8.5)");
}
