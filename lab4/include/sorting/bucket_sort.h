#pragma once
#include <vector>
#include <algorithm>
#include <iterator>
#include "selection_sort.h"

inline void bucketSort(std::vector<double>& arr) {
    if (arr.empty()) return;
    size_t n = arr.size();
    std::vector<std::vector<double>> buckets(n);

    double max_val = *std::max_element(arr.begin(), arr.end());
    double min_val = *std::min_element(arr.begin(), arr.end());

    if (max_val == min_val) return;

    for (double val : arr) {
        size_t bi = static_cast<size_t>(n * (val - min_val) / (max_val - min_val + 1e-9));
        if (bi >= n) bi = n - 1;
        buckets[bi].push_back(val);
    }

    arr.clear();
    for (auto& bucket : buckets) {
        selectionSort(bucket);
        arr.insert(arr.end(), bucket.begin(), bucket.end());
    }
}
