#pragma once

#include <string>

namespace docflow {

class DocumentMetadata {
public:
    DocumentMetadata() = default;
    DocumentMetadata(long createdTs, long modifiedTs, std::string lang, int securityLevel);
    void updateModificationTime(long newTimestamp);
    void escalateSecurityLevel(int deltaLevel);
    int getSecurityLevel() const;
    long getModifiedTimestamp() const;

private:
    long createdTimestamp_{0};
    long modifiedTimestamp_{0};
    std::string languageCode_{"RU"};
    int securityLevel_{1};
};

}
