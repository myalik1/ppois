#pragma once

#include <string>

namespace docflow {

class EscalationRule {
public:
    EscalationRule(std::string ruleId, int maxPendingHours, std::string backupApproverId);
    bool shouldEscalate(int elapsedHours) const;
    std::string resolveApprover(int elapsedHours, const std::string& originalApprover) const;

private:
    std::string ruleId_;
    int maxPendingHours_;
    std::string backupApproverId_;
};

}
