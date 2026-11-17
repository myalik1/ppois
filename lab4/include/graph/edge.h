#pragma once
#include "vertex.h"

template <typename T>
class Edge {
private:
    Vertex<T> v1_;
    Vertex<T> v2_;
    double weight_;

public:
    Edge(const Vertex<T>& v1, const Vertex<T>& v2, double weight = 1.0)
        : v1_(v1), v2_(v2), weight_(weight) {}

    const Vertex<T>& getFirst() const { return v1_; }
    const Vertex<T>& getSecond() const { return v2_; }
    double getWeight() const { return weight_; }
    void setWeight(double w) { weight_ = w; }

    bool operator==(const Edge& other) const {
        return (v1_ == other.v1_ && v2_ == other.v2_) || (v1_ == other.v2_ && v2_ == other.v1_);
    }
    bool operator!=(const Edge& other) const { return !(*this == other); }
    bool operator<(const Edge& other) const { return weight_ < other.weight_; }
    bool operator>(const Edge& other) const { return other < *this; }
    bool operator<=(const Edge& other) const { return !(*this > other); }
    bool operator>=(const Edge& other) const { return !(*this < other); }
};
