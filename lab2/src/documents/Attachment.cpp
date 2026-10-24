#include "../../include/documents/Attachment.h"

namespace docflow {

Attachment::Attachment(
    std::string fileName, std::string mimeType, std::size_t sizeBytes, std::string hash)
    : fileName_(std::move(fileName)),
      mimeType_(std::move(mimeType)),
      fileSizeBytes_(sizeBytes),
      checksum_(std::move(hash)) {}

bool Attachment::verifyChecksum(const std::string& expectedHash) const {
    return !expectedHash.empty() && checksum_ == expectedHash;
}

bool Attachment::exceedsSizeLimit(std::size_t maxBytes) const {
    return fileSizeBytes_ > maxBytes;
}

const std::string& Attachment::getFileName() const {
    return fileName_;
}

}
