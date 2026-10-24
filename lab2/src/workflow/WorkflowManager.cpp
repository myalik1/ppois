#include "../../include/workflow/WorkflowManager.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

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
