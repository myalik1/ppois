#pragma once
#include <iterator>
#include <vector>
#include "edge.h"

template <typename T>
class IncidentEdgeIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Edge<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = Edge<T>*;
    using reference = Edge<T>&;

    explicit IncidentEdgeIterator(typename std::vector<Edge<T>*>::iterator ptr) : ptr_(ptr) {}

    reference operator*() const { return **ptr_; }
    pointer operator->() const { return *ptr_; }

    IncidentEdgeIterator& operator++() { ++ptr_; return *this; }
    IncidentEdgeIterator operator++(int) { IncidentEdgeIterator tmp = *this; ++ptr_; return tmp; }
    IncidentEdgeIterator& operator--() { --ptr_; return *this; }
    IncidentEdgeIterator operator--(int) { IncidentEdgeIterator tmp = *this; --ptr_; return tmp; }

    bool operator==(const IncidentEdgeIterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const IncidentEdgeIterator& other) const { return ptr_ != other.ptr_; }

private:
    typename std::vector<Edge<T>*>::iterator ptr_;
};

template <typename T>
class ConstIncidentEdgeIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const Edge<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = const Edge<T>*;
    using reference = const Edge<T>&;

    explicit ConstIncidentEdgeIterator(typename std::vector<Edge<T>*>::const_iterator ptr) : ptr_(ptr) {}

    reference operator*() const { return **ptr_; }
    pointer operator->() const { return *ptr_; }

    ConstIncidentEdgeIterator& operator++() { ++ptr_; return *this; }
    ConstIncidentEdgeIterator operator++(int) { ConstIncidentEdgeIterator tmp = *this; ++ptr_; return tmp; }
    ConstIncidentEdgeIterator& operator--() { --ptr_; return *this; }
    ConstIncidentEdgeIterator operator--(int) { ConstIncidentEdgeIterator tmp = *this; --ptr_; return tmp; }

    bool operator==(const ConstIncidentEdgeIterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const ConstIncidentEdgeIterator& other) const { return ptr_ != other.ptr_; }

private:
    typename std::vector<Edge<T>*>::const_iterator ptr_;
};
