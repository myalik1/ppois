#pragma once
#include <iterator>
#include <vector>
#include "vertex.h"

template <typename T, typename Container>
class VertexIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Vertex<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = Vertex<T>*;
    using reference = value_type&;

    explicit VertexIterator(typename std::vector<Vertex<T>>::iterator ptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return &(*ptr_); }

    VertexIterator& operator++() { ++ptr_; return *this; }
    VertexIterator operator++(int) { VertexIterator tmp = *this; ++ptr_; return tmp; }
    VertexIterator& operator--() { --ptr_; return *this; }
    VertexIterator operator--(int) { VertexIterator tmp = *this; --ptr_; return tmp; }

    bool operator==(const VertexIterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const VertexIterator& other) const { return ptr_ != other.ptr_; }

    auto getBase() const { return ptr_; }

private:
    typename std::vector<Vertex<T>>::iterator ptr_;
};

template <typename T>
class ConstVertexIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const Vertex<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = const Vertex<T>*;
    using reference = const value_type&;

    explicit ConstVertexIterator(typename std::vector<Vertex<T>>::const_iterator ptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return &(*ptr_); }

    ConstVertexIterator& operator++() { ++ptr_; return *this; }
    ConstVertexIterator operator++(int) { ConstVertexIterator tmp = *this; ++ptr_; return tmp; }
    ConstVertexIterator& operator--() { --ptr_; return *this; }
    ConstVertexIterator operator--(int) { ConstVertexIterator tmp = *this; --ptr_; return tmp; }

    bool operator==(const ConstVertexIterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const ConstVertexIterator& other) const { return ptr_ != other.ptr_; }

    auto getBase() const { return ptr_; }

private:
    typename std::vector<Vertex<T>>::const_iterator ptr_;
};
