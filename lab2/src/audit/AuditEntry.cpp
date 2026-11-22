#include "../../include/audit/AuditEntry.h"

namespace docflow {

AuditEntry::AuditEntry(std::string id, std::string actorId, std::string docId, std::string action)
    : entryId_(std::move(id)),
      actorUserId_(std::move(actorId)),
      targetDocumentId_(std::move(docId)),
      actionName_(std::move(action)) {}

std::string AuditEntry::formatLogLine() const {
    return entryId_ + ":" + actorUserId_ + ":" + actionName_ + ":" + targetDocumentId_;
}

bool AuditEntry::involvesDocument(const Document& document) const {
    const std::string& docId = document.getDocumentId();
    return targetDocumentId_ == docId;
}

const std::string& AuditEntry::getActorUserId() const {
    return actorUserId_;
}

}
