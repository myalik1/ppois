#include "../../include/audit/AuditLogger.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

AuditLogger::AuditLogger(std::string loggerName, std::size_t maxEntries)
    : loggerName_(std::move(loggerName)), maxEntries_(maxEntries) {}

void AuditLogger::recordAction(
    const User& actor, const Document& document, const std::string& action) {
    if (entries_.size() >= maxEntries_) {
        throw StorageCapacityExceededException("Audit log capacity reached");
    }
    std::string entryId = "AUD-" + std::to_string(entries_.size() + 1);
    entries_.emplace_back(entryId, actor.getUserId(), document.getDocumentId(), action);
}

std::size_t AuditLogger::countActionsByUser(const std::string& userId) const {
    std::size_t count = 0;
    for (const auto& entry : entries_) {
        if (entry.getActorUserId() == userId) {
            count += 1;
        }
    }
    return count;
}

void AuditLogger::clearOldEntries(std::size_t keepCount) {
    if (entries_.size() <= keepCount) {
        return;
    }
    std::size_t eraseCount = entries_.size() - keepCount;
    entries_.erase(entries_.begin(), entries_.begin() + static_cast<std::ptrdiff_t>(eraseCount));
}

std::size_t AuditLogger::getEntriesCount() const {
    return entries_.size();
}

}
