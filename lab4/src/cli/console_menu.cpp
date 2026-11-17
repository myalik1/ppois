#include "../../include/cli/console_menu.h"
#include "../../include/sorting/selection_sort.h"
#include "../../include/sorting/bucket_sort.h"
#include <iostream>
#include <limits>

void ConsoleMenu::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Vertex<std::string>* ConsoleMenu::findVertexByName(const std::string& name) {
    for (auto it = graph_.begin(); it != graph_.end(); ++it) {
        if (it->getData() == name) {
            return &(*it);
        }
    }
    return nullptr;
}

void ConsoleMenu::handleSelectionSort() {
    size_t count = 0;
    std::cout << "Enter number of integer elements: ";
    if (!(std::cin >> count) || count == 0) {
        std::cout << "Invalid count.\n";
        clearInputBuffer();
        return;
    }

    std::vector<int> data(count);
    std::cout << "Enter " << count << " integers separated by space: ";
    for (size_t i = 0; i < count; ++i) {
        if (!(std::cin >> data[i])) {
            std::cout << "Invalid input format.\n";
            clearInputBuffer();
            return;
        }
    }

    selectionSort(data);
    std::cout << "Sorted result (Selection Sort): ";
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void ConsoleMenu::handleBucketSort() {
    size_t count = 0;
    std::cout << "Enter number of floating-point elements: ";
    if (!(std::cin >> count) || count == 0) {
        std::cout << "Invalid count.\n";
        clearInputBuffer();
        return;
    }

    std::vector<double> data(count);
    std::cout << "Enter " << count << " numbers (e.g. 0.42 0.15 0.89): ";
    for (size_t i = 0; i < count; ++i) {
        if (!(std::cin >> data[i])) {
            std::cout << "Invalid input format.\n";
            clearInputBuffer();
            return;
        }
    }

    bucketSort(data);
    std::cout << "Sorted result (Bucket Sort): ";
    for (double val : data) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void ConsoleMenu::handleGraphMenu() {
    int subChoice = -1;
    while (subChoice != 0) {
        std::cout << "\n--- Undirected Graph Interactive Menu ---\n"
                  << "1. Add vertex\n"
                  << "2. Add edge\n"
                  << "3. Remove vertex\n"
                  << "4. Remove edge\n"
                  << "5. Show vertex info (degree & adjacent vertices)\n"
                  << "6. Print full graph\n"
                  << "7. Clear graph\n"
                  << "0. Back to main menu\n"
                  << "Choice: ";

        if (!(std::cin >> subChoice)) {
            clearInputBuffer();
            continue;
        }

        try {
            if (subChoice == 1) {
                std::string name;
                std::cout << "Enter vertex label: ";
                std::cin >> name;
                if (findVertexByName(name) != nullptr) {
                    std::cout << "Vertex '" << name << "' already exists.\n";
                } else {
                    graph_.addVertex(Vertex<std::string>(name));
                    std::cout << "Vertex '" << name << "' added.\n";
                }
            } else if (subChoice == 2) {
                std::string name1, name2;
                double weight = 1.0;
                std::cout << "Enter first vertex label: ";
                std::cin >> name1;
                std::cout << "Enter second vertex label: ";
                std::cin >> name2;
                std::cout << "Enter edge weight: ";
                if (!(std::cin >> weight)) {
                    clearInputBuffer();
                    std::cout << "Invalid weight.\n";
                    continue;
                }

                const auto* v1 = findVertexByName(name1);
                const auto* v2 = findVertexByName(name2);
                if (!v1 || !v2) {
                    std::cout << "Error: Both vertices must exist in the graph.\n";
                } else {
                    graph_.addEdge(*v1, *v2, weight);
                    std::cout << "Edge (" << name1 << " - " << name2 << ") added.\n";
                }
            } else if (subChoice == 3) {
                std::string name;
                std::cout << "Enter vertex label to remove: ";
                std::cin >> name;
                const auto* v = findVertexByName(name);
                if (!v) {
                    std::cout << "Vertex not found.\n";
                } else {
                    graph_.removeVertex(*v);
                    std::cout << "Vertex '" << name << "' removed.\n";
                }
            } else if (subChoice == 4) {
                std::string name1, name2;
                std::cout << "Enter first vertex label: ";
                std::cin >> name1;
                std::cout << "Enter second vertex label: ";
                std::cin >> name2;
                const auto* v1 = findVertexByName(name1);
                const auto* v2 = findVertexByName(name2);
                if (!v1 || !v2) {
                    std::cout << "One or both vertices not found.\n";
                } else {
                    graph_.removeEdge(*v1, *v2);
                    std::cout << "Edge removed.\n";
                }
            } else if (subChoice == 5) {
                std::string name;
                std::cout << "Enter vertex label: ";
                std::cin >> name;
                const auto* v = findVertexByName(name);
                if (!v) {
                    std::cout << "Vertex not found.\n";
                } else {
                    std::cout << "Degree of '" << name << "': " << graph_.vertexDegree(*v) << "\n";
                    std::cout << "Adjacent vertices: ";
                    for (auto it = graph_.adjacentBegin(*v); it != graph_.adjacentEnd(*v); ++it) {
                        std::cout << it->getData() << " ";
                    }
                    std::cout << "\n";
                }
            } else if (subChoice == 6) {
                if (graph_.empty()) {
                    std::cout << "Graph is empty.\n";
                } else {
                    std::cout << graph_ << "\n";
                }
            } else if (subChoice == 7) {
                graph_.clear();
                std::cout << "Graph cleared.\n";
            }
        } catch (const std::exception& ex) {
            std::cout << "Operation error: " << ex.what() << "\n";
        }
    }
}

void ConsoleMenu::run() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== LAB 4: Variant 5 (Interactive CLI) ===\n"
                  << "1. Selection Sort (custom integer array)\n"
                  << "2. Bucket Sort (custom floating-point array)\n"
                  << "3. Undirected Graph Workspace\n"
                  << "0. Exit\n"
                  << "Select option: ";

        if (!(std::cin >> choice)) {
            clearInputBuffer();
            continue;
        }

        if (choice == 1) {
            handleSelectionSort();
        } else if (choice == 2) {
            handleBucketSort();
        } else if (choice == 3) {
            handleGraphMenu();
        }
    }
}
