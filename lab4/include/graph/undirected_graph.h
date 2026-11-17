#pragma once
#include <algorithm>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <vector>
#include "vertex.h"
#include "edge.h"
#include "vertex_iterator.h"
#include "edge_iterator.h"
#include "incident_edge_iterator.h"
#include "adjacent_vertex_iterator.h"

template <typename T>
class UndirectedGraph {
private:
    std::vector<Vertex<T>> vertices_;
    std::vector<Edge<T>> edges_;
    std::vector<std::vector<Edge<T>*>> adjacency_list_;
    std::vector<std::vector<Vertex<T>*>> adjacent_vertices_list_;

    int findVertexIndex(const Vertex<T>& v) const {
        for (size_t i = 0; i < vertices_.size(); ++i) {
            if (vertices_[i] == v) return static_cast<int>(i);
        }
        return -1;
    }

    void rebuildAdjacency() {
        adjacency_list_.assign(vertices_.size(), {});
        adjacent_vertices_list_.assign(vertices_.size(), {});

        for (size_t i = 0; i < edges_.size(); ++i) {
            int u = findVertexIndex(edges_[i].getFirst());
            int v = findVertexIndex(edges_[i].getSecond());
            if (u != -1 && v != -1) {
                adjacency_list_[u].push_back(&edges_[i]);
                adjacency_list_[v].push_back(&edges_[i]);
                adjacent_vertices_list_[u].push_back(&vertices_[v]);
                adjacent_vertices_list_[v].push_back(&vertices_[u]);
            }
        }
    }

public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using vertex_type = Vertex<T>;
    using edge_type = Edge<T>;
    using reference = Vertex<T>&;
    using const_reference = const Vertex<T>&;

    using iterator = VertexIterator<T, std::vector<Vertex<T>>>;
    using const_iterator = ConstVertexIterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using edge_iterator = EdgeIterator<T>;
    using const_edge_iterator = ConstEdgeIterator<T>;
    using reverse_edge_iterator = std::reverse_iterator<edge_iterator>;
    using const_reverse_edge_iterator = std::reverse_iterator<const_edge_iterator>;

    using incident_edge_iterator = IncidentEdgeIterator<T>;
    using const_incident_edge_iterator = ConstIncidentEdgeIterator<T>;
    using reverse_incident_edge_iterator = std::reverse_iterator<incident_edge_iterator>;
    using const_reverse_incident_edge_iterator = std::reverse_iterator<const_incident_edge_iterator>;

    using adjacent_vertex_iterator = AdjacentVertexIterator<T>;
    using const_adjacent_vertex_iterator = ConstAdjacentVertexIterator<T>;
    using reverse_adjacent_vertex_iterator = std::reverse_iterator<adjacent_vertex_iterator>;
    using const_reverse_adjacent_vertex_iterator = std::reverse_iterator<const_adjacent_vertex_iterator>;

    UndirectedGraph() = default;

    UndirectedGraph(const UndirectedGraph& other) {
        *this = other;
    }

    ~UndirectedGraph() = default;

    UndirectedGraph& operator=(const UndirectedGraph& other) {
        if (this == &other) return *this;
        vertices_ = other.vertices_;
        edges_ = other.edges_;
        rebuildAdjacency();
        return *this;
    }

    bool empty() const { return vertices_.empty(); }
    void clear() {
        vertices_.clear();
        edges_.clear();
        adjacency_list_.clear();
        adjacent_vertices_list_.clear();
    }

    bool hasVertex(const Vertex<T>& v) const {
        return findVertexIndex(v) != -1;
    }

    bool hasEdge(const Vertex<T>& v1, const Vertex<T>& v2) const {
        int u = findVertexIndex(v1);
        int w = findVertexIndex(v2);
        if (u == -1 || w == -1) return false;
        for (const auto* edge : adjacency_list_[u]) {
            if ((edge->getFirst() == v1 && edge->getSecond() == v2) ||
                (edge->getFirst() == v2 && edge->getSecond() == v1)) {
                return true;
            }
        }
        return false;
    }

    size_t vertexCount() const { return vertices_.size(); }
    size_t edgeCount() const { return edges_.size(); }

    size_t vertexDegree(const Vertex<T>& v) const {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return adjacency_list_[idx].size();
    }

    size_t edgeDegree(const Edge<T>& e) const {
        if (!hasEdge(e.getFirst(), e.getSecond())) throw std::out_of_range("Edge not found");
        return vertexDegree(e.getFirst()) + vertexDegree(e.getSecond()) - 2;
    }

    void addVertex(const Vertex<T>& v) {
        if (hasVertex(v)) return;
        vertices_.push_back(v);
        rebuildAdjacency();
    }

    void addEdge(const Vertex<T>& v1, const Vertex<T>& v2, double weight = 1.0) {
        int u = findVertexIndex(v1);
        int w = findVertexIndex(v2);
        if (u == -1 || w == -1) throw std::out_of_range("Vertices must exist before adding edge");
        if (hasEdge(v1, v2)) return;

        edges_.emplace_back(v1, v2, weight);
        rebuildAdjacency();
    }

    void removeVertex(const Vertex<T>& v) {
        int idx = findVertexIndex(v);
        if (idx == -1) return;

        edges_.erase(
            std::remove_if(edges_.begin(), edges_.end(), [&](const Edge<T>& e) {
                return e.getFirst() == v || e.getSecond() == v;
            }),
            edges_.end()
        );

        vertices_.erase(vertices_.begin() + idx);
        rebuildAdjacency();
    }

    void removeEdge(const Vertex<T>& v1, const Vertex<T>& v2) {
        int u = findVertexIndex(v1);
        int w = findVertexIndex(v2);
        if (u == -1 || w == -1) return;

        auto it = std::find_if(edges_.begin(), edges_.end(), [&](const Edge<T>& e) {
            return (e.getFirst() == v1 && e.getSecond() == v2) ||
                   (e.getFirst() == v2 && e.getSecond() == v1);
        });

        if (it != edges_.end()) {
            edges_.erase(it);
            rebuildAdjacency();
        }
    }

    void removeVertex(iterator it) {
        if (it.getBase() != vertices_.end()) {
            removeVertex(*it);
        }
    }

    void removeEdge(edge_iterator it) {
        if (it.getBase() != edges_.end()) {
            removeEdge(it->getFirst(), it->getSecond());
        }
    }

    iterator begin() { return iterator(vertices_.begin()); }
    iterator end() { return iterator(vertices_.end()); }
    const_iterator begin() const { return const_iterator(vertices_.cbegin()); }
    const_iterator end() const { return const_iterator(vertices_.cend()); }
    const_iterator cbegin() const { return const_iterator(vertices_.cbegin()); }
    const_iterator cend() const { return const_iterator(vertices_.cend()); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

    edge_iterator edgesBegin() { return edge_iterator(edges_.begin()); }
    edge_iterator edgesEnd() { return edge_iterator(edges_.end()); }
    const_edge_iterator edgesBegin() const { return const_edge_iterator(edges_.cbegin()); }
    const_edge_iterator edgesEnd() const { return const_edge_iterator(edges_.cend()); }
    const_edge_iterator edgesCBegin() const { return const_edge_iterator(edges_.cbegin()); }
    const_edge_iterator edgesCEnd() const { return const_edge_iterator(edges_.cend()); }
    reverse_edge_iterator edgesRBegin() { return reverse_edge_iterator(edgesEnd()); }
    reverse_edge_iterator edgesREnd() { return reverse_edge_iterator(edgesBegin()); }
    const_reverse_edge_iterator edgesRBegin() const { return const_reverse_edge_iterator(edgesEnd()); }
    const_reverse_edge_iterator edgesREnd() const { return const_reverse_edge_iterator(edgesBegin()); }

    incident_edge_iterator incidentBegin(const Vertex<T>& v) {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return incident_edge_iterator(adjacency_list_[idx].begin());
    }
    incident_edge_iterator incidentEnd(const Vertex<T>& v) {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return incident_edge_iterator(adjacency_list_[idx].end());
    }
    const_incident_edge_iterator incidentBegin(const Vertex<T>& v) const {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return const_incident_edge_iterator(adjacency_list_[idx].cbegin());
    }
    const_incident_edge_iterator incidentEnd(const Vertex<T>& v) const {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return const_incident_edge_iterator(adjacency_list_[idx].cend());
    }
    reverse_incident_edge_iterator incidentRBegin(const Vertex<T>& v) {
        return reverse_incident_edge_iterator(incidentEnd(v));
    }
    reverse_incident_edge_iterator incidentREnd(const Vertex<T>& v) {
        return reverse_incident_edge_iterator(incidentBegin(v));
    }
    const_reverse_incident_edge_iterator incidentRBegin(const Vertex<T>& v) const {
        return const_reverse_incident_edge_iterator(incidentEnd(v));
    }
    const_reverse_incident_edge_iterator incidentREnd(const Vertex<T>& v) const {
        return const_reverse_incident_edge_iterator(incidentBegin(v));
    }

    adjacent_vertex_iterator adjacentBegin(const Vertex<T>& v) {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return adjacent_vertex_iterator(adjacent_vertices_list_[idx].begin());
    }
    adjacent_vertex_iterator adjacentEnd(const Vertex<T>& v) {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return adjacent_vertex_iterator(adjacent_vertices_list_[idx].end());
    }
    const_adjacent_vertex_iterator adjacentBegin(const Vertex<T>& v) const {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return const_adjacent_vertex_iterator(adjacent_vertices_list_[idx].cbegin());
    }
    const_adjacent_vertex_iterator adjacentEnd(const Vertex<T>& v) const {
        int idx = findVertexIndex(v);
        if (idx == -1) throw std::out_of_range("Vertex not found");
        return const_adjacent_vertex_iterator(adjacent_vertices_list_[idx].cend());
    }
    reverse_adjacent_vertex_iterator adjacentRBegin(const Vertex<T>& v) {
        return reverse_adjacent_vertex_iterator(adjacentEnd(v));
    }
    reverse_adjacent_vertex_iterator adjacentREnd(const Vertex<T>& v) {
        return reverse_adjacent_vertex_iterator(adjacentBegin(v));
    }
    const_reverse_adjacent_vertex_iterator adjacentRBegin(const Vertex<T>& v) const {
        return const_reverse_adjacent_vertex_iterator(adjacentEnd(v));
    }
    const_reverse_adjacent_vertex_iterator adjacentREnd(const Vertex<T>& v) const {
        return const_reverse_adjacent_vertex_iterator(adjacentBegin(v));
    }

    bool operator==(const UndirectedGraph& other) const {
        return vertices_ == other.vertices_ && edges_ == other.edges_;
    }
    bool operator!=(const UndirectedGraph& other) const { return !(*this == other); }
    bool operator<(const UndirectedGraph& other) const {
        if (vertices_.size() != other.vertices_.size()) {
            return vertices_.size() < other.vertices_.size();
        }
        return edges_.size() < other.edges_.size();
    }
    bool operator>(const UndirectedGraph& other) const { return other < *this; }
    bool operator<=(const UndirectedGraph& other) const { return !(*this > other); }
    bool operator>=(const UndirectedGraph& other) const { return !(*this < other); }

    friend std::ostream& operator<<(std::ostream& os, const UndirectedGraph& g) {
        os << "UndirectedGraph [Vertices: " << g.vertexCount() << ", Edges: " << g.edgeCount() << "]\n";
        os << "Vertices: ";
        std::for_each(g.begin(), g.end(), [&os](const Vertex<T>& v) {
            os << v.getData() << " ";
        });
        os << "\nEdges: ";
        std::for_each(g.edgesBegin(), g.edgesEnd(), [&os](const Edge<T>& e) {
            os << "(" << e.getFirst().getData() << " - " << e.getSecond().getData()
               << ", w:" << e.getWeight() << ") ";
        });
        return os;
    }
};
