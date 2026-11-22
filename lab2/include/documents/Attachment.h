#pragma once

#include <cstddef>
#include <string>

namespace docflow {

class Attachment {
public:
    Attachment(std::string fileName, std::string mimeType, std::size_t sizeBytes, std::string hash);
    bool verifyChecksum(const std::string& expectedHash) const;
    bool exceedsSizeLimit(std::size_t maxBytes) const;
    const std::string& getFileName() const;

private:
    std::string fileName_;
    std::string mimeType_;
    std::size_t fileSizeBytes_;
    std::string checksum_;
};

}
