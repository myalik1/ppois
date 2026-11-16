#include "../../include/search/SearchEngine.h"

namespace docflow {

SearchEngine::SearchEngine(std::string engineName) : engineName_(std::move(engineName)) {}

void SearchEngine::indexDocument(const Document& document) {
    const std::string& docId = document.getDocumentId();
    std::vector<std::string> terms{document.getTitle(), document.getStatus()};
    for (const auto& tag : document.getTags()) {
        terms.push_back(tag.getTagName());
    }
    int boost = document.getMetadata().getSecurityLevel();
    entries_[docId] = IndexEntry(docId, terms, boost);
}

std::vector<std::string> SearchEngine::searchByTerm(const std::string& term) {
    queryCounter_ += 1;
    std::vector<std::string> matchedIds;
    for (const auto& pair : entries_) {
        if (pair.second.containsTerm(term)) {
            matchedIds.push_back(pair.first);
        }
    }
    return matchedIds;
}

std::vector<Document> SearchEngine::filterDocuments(
    const std::vector<Document>& docs, const SearchFilter& filter) {
    queryCounter_ += 1;
    std::vector<Document> result;
    for (const auto& doc : docs) {
        if (filter.matchesDocument(doc)) {
            result.push_back(doc);
        }
    }
    return result;
}

int SearchEngine::getQueryCounter() const {
    return queryCounter_;
}

}
