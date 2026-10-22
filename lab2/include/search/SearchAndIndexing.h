#pragma once

#include "../documents/DocumentCore.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace docflow {

class SearchFilter {
public:
    SearchFilter(std::string titleSubstring, std::string requiredStatus, int minSecurityLevel);
    bool matchesDocument(const Document& document) const;
    bool isFilterEmpty() const;

private:
    std::string titleSubstring_;
    std::string requiredStatus_;
    int minSecurityLevel_;
};

class IndexEntry {
public:
    IndexEntry() = default;
    IndexEntry(std::string documentId, std::vector<std::string> terms, int relevanceBoost);
    bool containsTerm(const std::string& term) const;
    int scoreTermMatch(const std::string& queryTerm) const;

private:
    std::string documentId_;
    std::vector<std::string> tokenizedTerms_;
    int relevanceBoost_{1};
};

class TagRegistry {
public:
    TagRegistry(std::string registryName, std::size_t maxTagsAllowed);
    void registerTag(const Tag& tag);
    Tag findTagByName(const std::string& name) const;
    std::size_t countTags() const;

private:
    std::string registryName_;
    std::size_t maxTagsAllowed_;
    std::vector<Tag> registeredTags_;
};

class DocumentSorter {
public:
    DocumentSorter(std::string sortField, bool ascendingOrder);
    void sortByTitle(std::vector<Document>& documents) const;
    void sortBySecurityLevel(std::vector<Document>& documents) const;

private:
    std::string sortField_;
    bool ascendingOrder_;
};

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
