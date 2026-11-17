#pragma once
#include <string>
#include <vector>
#include "../graph/undirected_graph.h"

class ConsoleMenu {
private:
    UndirectedGraph<std::string> graph_;

    static void handleSelectionSort();
    static void handleBucketSort();
    void handleGraphMenu();

    Vertex<std::string>* findVertexByName(const std::string& name);
    static void clearInputBuffer();

public:
    void run();
};
