#pragma once

#include "../core/User.h"
#include <string>

namespace docflow {

class ApprovalStep {
public:
    ApprovalStep(int stepOrder, std::string approverUserId);
    void approveStep(const User& approver, const std::string& comment);
    void rejectStep(const User& approver, const std::string& reason);
    bool isApproved() const;
    const std::string& getApproverUserId() const;

private:
    int stepOrder_;
    std::string approverUserId_;
    bool approvedFlag_{false};
    std::string decisionComment_;
};

}
