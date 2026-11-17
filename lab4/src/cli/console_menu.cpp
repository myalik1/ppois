#include "../../include/cli/console_menu.h"
#include "../../include/sorting/selection_sort.h"
#include "../../include/sorting/bucket_sort.h"
#include "../../include/sorting/student_record.h"
#include <iostream>
#include <limits>
#include <vector>

void ConsoleMenu::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Vertex<std::string>* ConsoleMenu::findVertexByName(const std::string& name) {
    for (auto it = graph_.begin(); it != graph_.end(); ++it) {
        if (it->getData() == name) return &(*it);
    }
    return nullptr;
}

const Vertex<std::string>* ConsoleMenu::findVertexByName(const std::string& name) const {
    for (auto it = graph_.cbegin(); it != graph_.cend(); ++it) {
        if (it->getData() == name) return &(*it);
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
    std::cout << "Enter " << count << " integers: ";
    for (size_t i = 0; i < count; ++i) {
        if (!(std::cin >> data[i])) {
            std::cout << "Invalid input format.\n";
            clearInputBuffer();
            return;
        }
    }
    selectionSort(data);
    std::cout << "Sorted result (Selection Sort): ";
    for (int val : data) std::cout << val << " ";
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
    std::cout << "Enter " << count << " numbers: ";
    for (size_t i = 0; i < count; ++i) {
        if (!(std::cin >> data[i])) {
            std::cout << "Invalid input format.\n";
            clearInputBuffer();
            return;
        }
    }
    bucketSort(data);
    std::cout << "Sorted result (Bucket Sort): ";
    for (double val : data) std::cout << val << " ";
    std::cout << "\n";
}

void ConsoleMenu::handleCustomObjectSort() {
    size_t count = 0;
    std::cout << "Enter number of students: ";
    if (!(std::cin >> count) || count == 0) {
        std::cout << "Invalid count.\n";
        clearInputBuffer();
        return;
    }
    std::vector<StudentRecord> records;
    records.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        std::string name;
        double gpa = 0.0;
        std::cout << "Student #" << (i + 1) << " name and GPA: ";
        if (!(std::cin >> name >> gpa)) {
            std::cout << "Invalid input format.\n";
            clearInputBuffer();
            return;
        }
        records.emplace_back(name, gpa);
    }
    bucketSort(records);
    std::cout << "Sorted students (Bucket Sort): ";
    for (const auto& rec : records) std::cout << rec << " | ";
    std::cout << "\n";
}

void ConsoleMenu::menuAddVertex() {
    std::string name;
    std::cout << "Enter vertex label: ";
    std::cin >> name;
    if (findVertexByName(name) != nullptr) {
        std::cout << "Vertex '" << name << "' already exists.\n";
        return;
    }
    graph_.addVertex(Vertex<std::string>(name));
    std::cout << "Vertex '" << name << "' added.\n";
}

void ConsoleMenu::menuAddEdge() {
    std::string name1, name2;
    double weight = 1.0;
    std::cout << "Enter first vertex, second vertex, and weight: ";
    if (!(std::cin >> name1 >> name2 >> weight)) {
        clearInputBuffer();
        std::cout << "Invalid input.\n";
        return;
    }
    const auto* v1 = findVertexByName(name1);
    const auto* v2 = findVertexByName(name2);
    if (!v1 || !v2) {
        std::cout << "Error: Both vertices must exist in the graph.\n";
        return;
    }
    graph_.addEdge(*v1, *v2, weight);
    std::cout << "Edge (" << name1 << " - " << name2 << ") added.\n";
}

void ConsoleMenu::menuRemoveVertex() {
    std::string name;
    std::cout << "Enter vertex label to remove: ";
    std::cin >> name;
    const auto* v = findVertexByName(name);
    if (!v) {
        std::cout << "Vertex not found.\n";
        return;
    }
    graph_.removeVertex(*v);
    std::cout << "Vertex '" << name << "' removed.\n";
}

void ConsoleMenu::menuRemoveEdge() {
    std::string name1, name2;
    std::cout << "Enter first and second vertex labels: ";
    std::cin >> name1 >> name2;
    const auto* v1 = findVertexByName(name1);
    const auto* v2 = findVertexByName(name2);
    if (!v1 || !v2) {
        std::cout << "One or both vertices not found.\n";
        return;
    }
    graph_.removeEdge(*v1, *v2);
    std::cout << "Edge removed.\n";
}

void ConsoleMenu::menuShowVertexInfo() const {
    std::string name;
    std::cout << "Enter vertex label: ";
    std::cin >> name;
    const auto* v = findVertexByName(name);
    if (!v) {
        std::cout << "Vertex not found.\n";
        return;
    }
    std::cout << "Degree of '" << name << "': " << graph_.vertexDegree(*v) << "\n";
    std::cout << "Adjacent vertices: ";
    for (auto it = graph_.adjacentBegin(*v); it != graph_.adjacentEnd(*v); ++it) {
        std::cout << it->getData() << " ";
    }
    std::cout << "\n";
}

void ConsoleMenu::handleGraphMenu() {
    int sub_choice = -1;
    while (sub_choice != 0) {
        std::cout << "\n--- Undirected Graph Interactive Menu ---\n"
                  << "1. Add vertex\n2. Add edge\n3. Remove vertex\n4. Remove edge\n"
                  << "5. Show vertex info\n6. Print full graph\n7. Clear graph\n0. Back\nChoice: ";
        if (!(std::cin >> sub_choice)) {
            clearInputBuffer();
            continue;
        }
        try {
            if (sub_choice == 1) menuAddVertex();
            else if (sub_choice == 2) menuAddEdge();
            else if (sub_choice == 3) menuRemoveVertex();
            else if (sub_choice == 4) menuRemoveEdge();
            else if (sub_choice == 5) menuShowVertexInfo();
            else if (sub_choice == 6) {
                if (graph_.empty()) std::cout << "Graph is empty.\n";
                else std::cout << graph_ << "\n";
            } else if (sub_choice == 7) {
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
        std::cout << "\n=== Interactive CLI ===\n"
                  << "1. Selection Sort (integers)\n2. Bucket Sort (doubles)\n"
                  << "3. Sort Custom Class (StudentRecord)\n4. Undirected Graph Workspace\n0. Exit\nSelect: ";
        if (!(std::cin >> choice)) {
            clearInputBuffer();
            continue;
        }
        if (choice == 1) handleSelectionSort();
        else if (choice == 2) handleBucketSort();
        else if (choice == 3) handleCustomObjectSort();
        else if (choice == 4) handleGraphMenu();
    }
}
