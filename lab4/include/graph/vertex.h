#pragma once
#include <iostream>
template <typename T>
class Vertex {
private:
    T data_;
    size_t id_;
    static inline size_t counter_ = 0;

public:
    explicit Vertex(const T& data) : data_(data), id_(counter_++) {}

    const T& getData() const { return data_; }
    T& getData() { return data_; }

    void setData(const T& data) { data_ = data; }
    size_t getId() const { return id_; }

    bool operator==(const Vertex& other) const { return id_ == other.id_ && data_ == other.data_; }
    bool operator!=(const Vertex& other) const { return !(*this == other); }
    bool operator<(const Vertex& other) const { return id_ < other.id_; }
    bool operator>(const Vertex& other) const { return other < *this; }
    bool operator<=(const Vertex& other) const { return !(*this > other); }
    bool operator>=(const Vertex& other) const { return !(*this < other); }
};
