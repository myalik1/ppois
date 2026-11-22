#include "../../include/workflow/ApprovalStep.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

ApprovalStep::ApprovalStep(int stepOrder, std::string approverUserId)
    : stepOrder_(stepOrder), approverUserId_(std::move(approverUserId)) {}

void ApprovalStep::approveStep(const User& approver, const std::string& comment) {
    if (!approver.isActive() || approver.getUserId() != approverUserId_) {
        throw UnauthorizedAccessException("User is not authorized for this approval step");
    }
    approvedFlag_ = true;
    decisionComment_ = comment;
}

void ApprovalStep::rejectStep(const User& approver, const std::string& reason) {
    if (approver.getUserId() != approverUserId_ || reason.empty()) {
        throw WorkflowRouteException("Invalid rejection attempt on approval step");
    }
    approvedFlag_ = false;
    decisionComment_ = reason;
}

bool ApprovalStep::isApproved() const {
    return approvedFlag_;
}

const std::string& ApprovalStep::getApproverUserId() const {
    return approverUserId_;
}

}
