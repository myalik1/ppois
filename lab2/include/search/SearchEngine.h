#pragma once

#include "../documents/Document.h"
#include "IndexEntry.h"
#include "SearchFilter.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace docflow {

class SearchEngine {
public:
    explicit SearchEngine(std::string engineName);
    void indexDocument(const Document& document);
    std::vector<std::string> searchByTerm(const std::string& term);
    std::vector<Document> filterDocuments(
        const std::vector<Document>& docs, const SearchFilter& filter);
    int getQueryCounter() const;

private:
    std::string engineName_;
    std::map<std::string, IndexEntry> entries_;
    int queryCounter_{0};
};

}
