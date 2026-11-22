#include "../../include/workflow/ApprovalRoute.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

ApprovalRoute::ApprovalRoute(std::string routeId, std::string routeName)
    : routeId_(std::move(routeId)), routeName_(std::move(routeName)) {}

void ApprovalRoute::appendStep(const ApprovalStep& step) {
    if (step.getApproverUserId().empty()) {
        throw WorkflowRouteException("Approval step must specify an approver");
    }
    steps_.push_back(step);
}

bool ApprovalRoute::isFullyApproved() const {
    if (steps_.empty()) {
        return false;
    }
    for (const auto& step : steps_) {
        if (!step.isApproved()) {
            return false;
        }
    }
    return true;
}

std::size_t ApprovalRoute::currentStepIndex() const {
    for (std::size_t idx = 0; idx < steps_.size(); ++idx) {
        if (!steps_[idx].isApproved()) {
            return idx;
        }
    }
    return steps_.size();
}

std::vector<ApprovalStep>& ApprovalRoute::getSteps() {
    return steps_;
}

const std::vector<ApprovalStep>& ApprovalRoute::getSteps() const {
    return steps_;
}

}
