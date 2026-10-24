#include "../../include/search/IndexEntry.h"
#include <algorithm>

namespace docflow {

namespace {
const int kBaseTermScore = 10;
}

IndexEntry::IndexEntry(std::string documentId, std::vector<std::string> terms, int relevanceBoost)
    : documentId_(std::move(documentId)),
      tokenizedTerms_(std::move(terms)),
      relevanceBoost_(relevanceBoost) {}

bool IndexEntry::containsTerm(const std::string& term) const {
    return std::find(tokenizedTerms_.begin(), tokenizedTerms_.end(), term) != tokenizedTerms_.end();
}

int IndexEntry::scoreTermMatch(const std::string& queryTerm) const {
    if (!containsTerm(queryTerm)) {
        return 0;
    }
    return kBaseTermScore * relevanceBoost_;
}

}
