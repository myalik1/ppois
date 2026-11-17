#pragma once
#include <string>
#include "../graph/undirected_graph.h"

class ConsoleMenu {
private:
    UndirectedGraph<std::string> graph_;

    static void handleSelectionSort();
    static void handleBucketSort();
    static void handleCustomObjectSort();
    void handleGraphMenu();

    void menuAddVertex();
    void menuAddEdge();
    void menuRemoveVertex();
    void menuRemoveEdge();
    void menuShowVertexInfo() const;

    Vertex<std::string>* findVertexByName(const std::string& name);
    const Vertex<std::string>* findVertexByName(const std::string& name) const;
    static void clearInputBuffer();

public:
    void run();
};
