#pragma once

#include <cstddef>
#include <string>

namespace docflow {

class DocumentVersion {
public:
    DocumentVersion(int versionNumber, std::string authorId, std::string body, std::string summary);
    std::size_t calculateContentLength() const;
    bool containsKeyword(const std::string& keyword) const;
    int getVersionNumber() const;
    const std::string& getContentBody() const;

private:
    int versionNumber_;
    std::string authorId_;
    std::string contentBody_;
    std::string changeSummary_;
};

}
