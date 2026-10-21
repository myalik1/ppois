#include "../../include/workflow/WorkflowEngine.h"
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

WorkflowState::WorkflowState(
    std::string documentId, std::string stageName, int elapsedHours, bool blocked)
    : documentId_(std::move(documentId)),
      stageName_(std::move(stageName)),
      elapsedHours_(elapsedHours),
      blockedFlag_(blocked) {}

void WorkflowState::advanceHours(int hours) {
    if (hours < 0 || blockedFlag_) {
        throw InvalidDocumentStateException("Cannot advance hours on blocked or negative interval");
    }
    elapsedHours_ += hours;
}

void WorkflowState::moveToStage(const std::string& newStage) {
    if (newStage.empty() || blockedFlag_) {
        throw InvalidDocumentStateException("Cannot move blocked workflow state");
    }
    stageName_ = newStage;
}

int WorkflowState::getElapsedHours() const {
    return elapsedHours_;
}

const std::string& WorkflowState::getStageName() const {
    return stageName_;
}

bool WorkflowState::isBlocked() const {
    return blockedFlag_;
}

WorkflowManager::WorkflowManager(std::string managerId) : managerId_(std::move(managerId)) {}

void WorkflowManager::startWorkflow(Document& document, const ApprovalRoute& route) {
    if (route.getSteps().empty()) {
        throw WorkflowRouteException("Cannot start workflow with empty route");
    }
    const std::string& docId = document.getDocumentId();
    activeRoutes_[docId] = route;
    states_[docId] = WorkflowState(docId, "IN_REVIEW", 0, false);
    document.transitionStatus("IN_REVIEW");
}

void WorkflowManager::submitApproval(
    Document& document, const User& user, const std::string& comment) {
    const std::string& docId = document.getDocumentId();
    auto routeIt = activeRoutes_.find(docId);
    if (routeIt == activeRoutes_.end()) {
        throw WorkflowRouteException("Active route not found for document");
    }
    ApprovalRoute& route = routeIt->second;
    std::size_t index = route.currentStepIndex();
    if (index >= route.getSteps().size()) {
        throw InvalidDocumentStateException("All steps are already approved");
    }
    route.getSteps()[index].approveStep(user, comment);
    if (route.isFullyApproved()) {
        states_[docId].moveToStage("APPROVED");
        document.transitionStatus("APPROVED");
    }
}

std::string WorkflowManager::applyEscalation(
    const std::string& documentId, const EscalationRule& rule) {
    auto stateIt = states_.find(documentId);
    auto routeIt = activeRoutes_.find(documentId);
    if (stateIt == states_.end() || routeIt == activeRoutes_.end()) {
        throw WorkflowRouteException("Workflow not found for escalation");
    }
    std::size_t index = routeIt->second.currentStepIndex();
    const std::string& originalApprover = routeIt->second.getSteps()[index].getApproverUserId();
    int elapsed = stateIt->second.getElapsedHours();
    return rule.resolveApprover(elapsed, originalApprover);
}

const WorkflowState& WorkflowManager::getState(const std::string& documentId) const {
    auto it = states_.find(documentId);
    if (it == states_.end()) {
        throw DocumentNotFoundException("Workflow state not found");
    }
    return it->second;
}

}
