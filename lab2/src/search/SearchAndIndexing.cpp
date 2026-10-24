#include "../../include/search/SearchAndIndexing.h"
#include "../../include/exceptions/WorkflowExceptions.h"
#include <algorithm>

namespace docflow {

namespace {
const int kBaseTermScore = 10;
}

SearchFilter::SearchFilter(
    std::string titleSubstring, std::string requiredStatus, int minSecurityLevel)
    : titleSubstring_(std::move(titleSubstring)),
      requiredStatus_(std::move(requiredStatus)),
      minSecurityLevel_(minSecurityLevel) {}

bool SearchFilter::matchesDocument(const Document& document) const {
    const std::string& title = document.getTitle();
    bool titleOk = titleSubstring_.empty() || title.find(titleSubstring_) != std::string::npos;
    bool statusOk = requiredStatus_.empty() || document.getStatus() == requiredStatus_;
    int docSecurity = document.getMetadata().getSecurityLevel();
    return titleOk && statusOk && docSecurity >= minSecurityLevel_;
}

bool SearchFilter::isFilterEmpty() const {
    return titleSubstring_.empty() && requiredStatus_.empty() && minSecurityLevel_ <= 0;
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

TagRegistry::TagRegistry(std::string registryName, std::size_t maxTagsAllowed)
    : registryName_(std::move(registryName)), maxTagsAllowed_(maxTagsAllowed) {}

void TagRegistry::registerTag(const Tag& tag) {
    if (registeredTags_.size() >= maxTagsAllowed_) {
        throw StorageCapacityExceededException("Tag registry capacity reached");
    }
    registeredTags_.push_back(tag);
}

Tag TagRegistry::findTagByName(const std::string& name) const {
    for (const auto& tag : registeredTags_) {
        if (tag.getTagName() == name) {
            return tag;
        }
    }
    throw DocumentNotFoundException("Tag not found in registry");
}

std::size_t TagRegistry::countTags() const {
    return registeredTags_.size();
}

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
