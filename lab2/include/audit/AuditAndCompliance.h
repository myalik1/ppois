#pragma ocne

#include "../core/IdentityAndAccess.h"
#include "../documents/DocumentCore.h"
#include "../signatures/DigitalSignatures.h"
#include <cstddef>
#include <string>
#include <vector>

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

class AuditLogger {
public:
    AuditLogger(std::string loggerName, std::size_t maxEntries);
    void recordAction(const User& actor, const Document& document, const std::string& action);
    std::size_t countActionsByUser(const std::string& userId) const;
    void clearOldEntries(std::size_t keepCount);
    std::size_t getEntriesCount() const;

private:
    std::string loggerName_;
    std::size_t maxEntries_;
    std::vector<AuditEntry> entries_;
};

class ComplianceRule {
public:
    ComplianceRule(std::string ruleCode, std::size_t minVersions, bool requireSignature);
    bool checkVersionCount(const Document& document) const;
    bool evaluateCompliance(const Document& document, std::size_t signatureCount) const;

private:
    std::string ruleCode_;
    std::size_t minVersionsRequired_;
    bool requireSignature_;
};

class SecurityIncident {
public:
    SecurityIncident(std::string id, std::string offenderId, int severityScore, bool resolved);
    void resolveIncident();
    bool isCriticalIncident() const;
    bool isResolved() const;

private:
    std::string incidentId_;
    std::string offenderUserId_;
    int severityScore_;
    bool resolvedFlag_;
};

class ComplianceChecker {
public:
    explicit ComplianceChecker(std::string checkerName);
    void addRule(const ComplianceRule& rule);
    void verifyDocumentCompliance(
        const Document& document, const SignatureService& sigService) const;
    void registerIncident(const SecurityIncident& incident);
    std::size_t countIncidents() const;

private:
    std::string checkerName_;
    std::vector<ComplianceRule> rules_;
    std::vector<SecurityIncident> incidents_;
};

}
