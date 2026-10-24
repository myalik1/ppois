#pragma once

#include "../documents/Document.h"
#include <string>
#include <vector>

namespace docflow {

class DocumentSorter {
public:
    DocumentSorter(std::string sortField, bool ascendingOrder);
    void sortByTitle(std::vector<Document>& documents) const;
    void sortBySecurityLevel(std::vector<Document>& documents) const;

private:
    std::string sortField_;
    bool ascendingOrder_;
};

}
