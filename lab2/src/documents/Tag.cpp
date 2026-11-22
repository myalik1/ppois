#include "../../include/documents/Tag.h"

namespace docflow {

namespace {
const int kHighConfidentialityThreshold = 7;
}

Tag::Tag(std::string name, std::string category, int confidentialityWeight)
    : tagName_(std::move(name)),
      categoryName_(std::move(category)),
      confidentialityWeight_(confidentialityWeight) {}

bool Tag::isHighConfidentiality() const {
    return confidentialityWeight_ >= kHighConfidentialityThreshold;
}

bool Tag::matchesCategory(const std::string& category) const {
    return categoryName_ == category;
}

const std::string& Tag::getTagName() const {
    return tagName_;
}

}
