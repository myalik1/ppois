#include "../../include/audit/AuditAndCompliance.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const int kCriticalSeverityThreshold = 8;
}

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

ComplianceRule::ComplianceRule(std::string ruleCode, std::size_t minVersions, bool requireSignature)
    : ruleCode_(std::move(ruleCode)),
      minVersionsRequired_(minVersions),
      requireSignature_(requireSignature) {}

bool ComplianceRule::checkVersionCount(const Document& document) const {
    std::size_t count = document.getVersions().size();
    return count >= minVersionsRequired_;
}

bool ComplianceRule::evaluateCompliance(
    const Document& document, std::size_t signatureCount) const {
    bool versionsOk = checkVersionCount(document);
    bool signatureOk = !requireSignature_ || signatureCount > 0;
    return versionsOk && signatureOk;
}

SecurityIncident::SecurityIncident(
    std::string id, std::string offenderId, int severityScore, bool resolved)
    : incidentId_(std::move(id)),
      offenderUserId_(std::move(offenderId)),
      severityScore_(severityScore),
      resolvedFlag_(resolved) {}

void SecurityIncident::resolveIncident() {
    resolvedFlag_ = true;
}

bool SecurityIncident::isCriticalIncident() const {
    return severityScore_ >= kCriticalSeverityThreshold;
}

bool SecurityIncident::isResolved() const {
    return resolvedFlag_;
}

ComplianceChecker::ComplianceChecker(std::string checkerName)
    : checkerName_(std::move(checkerName)) {}

void ComplianceChecker::addRule(const ComplianceRule& rule) {
    rules_.push_back(rule);
}

void ComplianceChecker::verifyDocumentCompliance(
    const Document& document, const SignatureService& sigService) const {
    const std::string& docId = document.getDocumentId();
    std::size_t sigCount = sigService.countSignatures(docId);
    for (const auto& rule : rules_) {
        if (!rule.evaluateCompliance(document, sigCount)) {
            throw ComplianceViolationException("Document failed compliance check");
        }
    }
}

void ComplianceChecker::registerIncident(const SecurityIncident& incident) {
    incidents_.push_back(incident);
}

std::size_t ComplianceChecker::countIncidents() const {
    return incidents_.size();
}

}
