#include "../../include/audit/ComplianceChecker.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

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
