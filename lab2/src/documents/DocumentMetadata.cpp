#include "../../include/documents/DocumentMetadata.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const int kMaxSecurityLevel = 10;
}

DocumentMetadata::DocumentMetadata(
    long createdTs, long modifiedTs, std::string lang, int securityLevel)
    : createdTimestamp_(createdTs),
      modifiedTimestamp_(modifiedTs),
      languageCode_(std::move(lang)),
      securityLevel_(securityLevel) {}

void DocumentMetadata::updateModificationTime(long newTimestamp) {
    if (newTimestamp < createdTimestamp_) {
        throw InvalidDocumentDataException("Modification timestamp precedes creation");
    }
    modifiedTimestamp_ = newTimestamp;
}

void DocumentMetadata::escalateSecurityLevel(int deltaLevel) {
    int updatedLevel = securityLevel_ + deltaLevel;
    if (deltaLevel <= 0 || updatedLevel > kMaxSecurityLevel) {
        throw InvalidDocumentDataException("Invalid security escalation level");
    }
    securityLevel_ = updatedLevel;
}

int DocumentMetadata::getSecurityLevel() const {
    return securityLevel_;
}

long DocumentMetadata::getModifiedTimestamp() const {
    return modifiedTimestamp_;
}

}
