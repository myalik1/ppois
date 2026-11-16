#pragma once
#include <iterator>
#include <vector>
#include "vertex.h"

template <typename T>
class AdjacentVertexIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Vertex<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = Vertex<T>*;
    using reference = Vertex<T>&;

    explicit AdjacentVertexIterator(typename std::vector<Vertex<T>*>::iterator ptr) : ptr_(ptr) {}

    reference operator*() const { return **ptr_; }
    pointer operator->() const { return *ptr_; }

    AdjacentVertexIterator& operator++() { ++ptr_; return *this; }
    AdjacentVertexIterator operator++(int) { AdjacentVertexIterator tmp = *this; ++ptr_; return tmp; }
    AdjacentVertexIterator& operator--() { --ptr_; return *this; }
    AdjacentVertexIterator operator--(int) { AdjacentVertexIterator tmp = *this; --ptr_; return tmp; }

    bool operator==(const AdjacentVertexIterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const AdjacentVertexIterator& other) const { return ptr_ != other.ptr_; }

private:
    typename std::vector<Vertex<T>*>::iterator ptr_;
};
