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
