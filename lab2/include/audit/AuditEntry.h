#pragma once

#include "../documents/Document.h"
#include <string>

namespace docflow {

class AuditEntry {
public:
    AuditEntry(std::string id, std::string actorId, std::string docId, std::string action);
    std::string formatLogLine() const;
    bool involvesDocument(const Document& document) const;
    const std::string& getActorUserId() const;

private:
    std::string entryId_;
    std::string actorUserId_;
    std::string targetDocumentId_;
    std::string actionName_;
};

}
