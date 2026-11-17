#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>

template <typename RandomIt>
void selectionSort(RandomIt first, RandomIt last) {
    if (first == last) return;
    for (auto i = first; i != last; ++i) {
        auto min_it = i;
        for (auto j = std::next(i); j != last; ++j) {
            if (*j < *min_it) {
                min_it = j;
            }
        }
        if (min_it != i) {
            std::iter_swap(i, min_it);
        }
    }
}

template <typename Container>
void selectionSort(Container& container) {
    selectionSort(std::begin(container), std::end(container));
}

template <typename T>
void selectionSort(T* arr, std::size_t size) {
    if (arr == nullptr || size == 0) return;
    selectionSort(arr, arr + size);
}
