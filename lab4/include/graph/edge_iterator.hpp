#pragma once
#include <iterator>
#include <vector>
#include "edge.h"

template <typename T>
class EdgeIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Edge<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = Edge<T>*;
    using reference = Edge<T>&;

    explicit EdgeIterator(typename std::vector<Edge<T>>::iterator ptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return &(*ptr_); }

    EdgeIterator& operator++() { ++ptr_; return *this; }
    EdgeIterator operator++(int) { EdgeIterator tmp = *this; ++ptr_; return tmp; }
    EdgeIterator& operator--() { --ptr_; return *this; }
    EdgeIterator operator--(int) { EdgeIterator tmp = *this; --ptr_; return tmp; }

    bool operator==(const EdgeIterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const EdgeIterator& other) const { return ptr_ != other.ptr_; }

    auto getBase() const { return ptr_; }

private:
    typename std::vector<Edge<T>>::iterator ptr_;
};

template <typename T>
class ConstEdgeIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const Edge<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = const Edge<T>*;
    using reference = const Edge<T>&;

    explicit ConstEdgeIterator(typename std::vector<Edge<T>>::const_iterator ptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return &(*ptr_); }

    ConstEdgeIterator& operator++() { ++ptr_; return *this; }
    ConstEdgeIterator operator++(int) { ConstEdgeIterator tmp = *this; ++ptr_; return tmp; }
    ConstEdgeIterator& operator--() { --ptr_; return *this; }
    ConstEdgeIterator operator--(int) { ConstEdgeIterator tmp = *this; --ptr_; return tmp; }

    bool operator==(const ConstEdgeIterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const ConstEdgeIterator& other) const { return ptr_ != other.ptr_; }

    auto getBase() const { return ptr_; }

private:
    typename std::vector<Edge<T>>::const_iterator ptr_;
};
