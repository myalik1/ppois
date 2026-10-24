#include "../../include/documents/DocumentVersion.h"

namespace docflow {

DocumentVersion::DocumentVersion(
    int versionNumber, std::string authorId, std::string body, std::string summary)
    : versionNumber_(versionNumber),
      authorId_(std::move(authorId)),
      contentBody_(std::move(body)),
      changeSummary_(std::move(summary)) {}

std::size_t DocumentVersion::calculateContentLength() const {
    return contentBody_.size();
}

bool DocumentVersion::containsKeyword(const std::string& keyword) const {
    return !keyword.empty() && contentBody_.find(keyword) != std::string::npos;
}

int DocumentVersion::getVersionNumber() const {
    return versionNumber_;
}

const std::string& DocumentVersion::getContentBody() const {
    return contentBody_;
}

}
