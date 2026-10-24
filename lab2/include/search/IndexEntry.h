#pragma once

#include <string>
#include <vector>

namespace docflow {

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

}
