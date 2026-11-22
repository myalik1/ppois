#include "../../include/workflow/EscalationRule.h"

namespace docflow {

EscalationRule::EscalationRule(
    std::string ruleId, int maxPendingHours, std::string backupApproverId)
    : ruleId_(std::move(ruleId)),
      maxPendingHours_(maxPendingHours),
      backupApproverId_(std::move(backupApproverId)) {}

bool EscalationRule::shouldEscalate(int elapsedHours) const {
    return elapsedHours > maxPendingHours_;
}

std::string EscalationRule::resolveApprover(
    int elapsedHours, const std::string& originalApprover) const {
    if (shouldEscalate(elapsedHours)) {
        return backupApproverId_;
    }
    return originalApprover;
}

}
