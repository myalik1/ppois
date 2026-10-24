#include "../../include/search/SearchFilter.h"

namespace docflow {

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

}
