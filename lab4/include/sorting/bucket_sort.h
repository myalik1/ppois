#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>
#include "selection_sort.h"

namespace detail {
const double kBucketRangeEpsilon = 1e-9;

struct DefaultBucketKey {
    template <typename T>
    double operator()(const T& value) const {
        return static_cast<double>(value);
    }
};
}

template <typename RandomIt, typename KeyExtractor,
          typename = std::enable_if_t<!std::is_integral_v<KeyExtractor>>>
void bucketSort(RandomIt first, RandomIt last, KeyExtractor key_fn) {
    const auto distance = std::distance(first, last);
    if (distance <= 1) return;

    using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    const std::size_t count = static_cast<std::size_t>(distance);
    std::vector<std::vector<ValueType>> buckets(count);

    double min_key = key_fn(*first);
    double max_key = min_key;
    for (auto it = std::next(first); it != last; ++it) {
        const double current_key = key_fn(*it);
        if (current_key < min_key) min_key = current_key;
        if (current_key > max_key) max_key = current_key;
    }

    if (max_key == min_key) return;

    const double range = max_key - min_key + detail::kBucketRangeEpsilon;
    for (auto it = first; it != last; ++it) {
        const double normalized = (key_fn(*it) - min_key) / range;
        std::size_t bucket_idx = static_cast<std::size_t>(count * normalized);
        if (bucket_idx >= count) bucket_idx = count - 1;
        buckets[bucket_idx].push_back(*it);
    }

    auto out_it = first;
    for (auto& bucket : buckets) {
        selectionSort(bucket);
        out_it = std::move(bucket.begin(), bucket.end(), out_it);
    }
}

template <typename RandomIt>
void bucketSort(RandomIt first, RandomIt last) {
    bucketSort(first, last, detail::DefaultBucketKey{});
}

template <typename Container, typename KeyExtractor,
          typename = std::enable_if_t<!std::is_integral_v<KeyExtractor>>>
void bucketSort(Container& container, KeyExtractor key_fn) {
    bucketSort(std::begin(container), std::end(container), key_fn);
}

template <typename Container>
void bucketSort(Container& container) {
    bucketSort(std::begin(container), std::end(container), detail::DefaultBucketKey{});
}

template <typename T, typename KeyExtractor>
void bucketSort(T* arr, std::size_t size, KeyExtractor key_fn) {
    if (arr == nullptr || size <= 1) return;
    bucketSort(arr, arr + size, key_fn);
}

template <typename T>
void bucketSort(T* arr, std::size_t size) {
    bucketSort(arr, size, detail::DefaultBucketKey{});
}
