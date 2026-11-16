#pragma once

#include <string>

namespace docflow {

class Tag {
public:
    Tag(std::string name, std::string category, int confidentialityWeight);
    bool isHighConfidentiality() const;
    bool matchesCategory(const std::string& category) const;
    const std::string& getTagName() const;

private:
    std::string tagName_;
    std::string categoryName_;
    int confidentialityWeight_;
};

}
