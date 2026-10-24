#include "../../include/audit/ComplianceRule.h"

namespace docflow {

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

}
