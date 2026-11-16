#include "../../include/search/DocumentSorter.h"
#include <algorithm>

namespace docflow {

DocumentSorter::DocumentSorter(std::string sortField, bool ascendingOrder)
    : sortField_(std::move(sortField)), ascendingOrder_(ascendingOrder) {}

void DocumentSorter::sortByTitle(std::vector<Document>& documents) const {
    bool asc = ascendingOrder_;
    std::sort(documents.begin(), documents.end(), [asc](const Document& lhs, const Document& rhs) {
        return asc ? (lhs.getTitle() < rhs.getTitle()) : (lhs.getTitle() > rhs.getTitle());
    });
}

void DocumentSorter::sortBySecurityLevel(std::vector<Document>& documents) const {
    bool asc = ascendingOrder_;
    std::sort(documents.begin(), documents.end(), [asc](const Document& lhs, const Document& rhs) {
        int leftSec = lhs.getMetadata().getSecurityLevel();
        int rightSec = rhs.getMetadata().getSecurityLevel();
        return asc ? (leftSec < rightSec) : (leftSec > rightSec);
    });
}

}
