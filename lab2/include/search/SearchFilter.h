#pragma once

#include "../documents/Document.h"
#include <string>

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

}
