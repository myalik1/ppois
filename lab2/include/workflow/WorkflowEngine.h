#pragma once

#include "../core/IdentityAndAccess.h"
#include "../documents/DocumentCore.h"
#include <map>
#include <string>
#include <vector>

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

class ApprovalRoute {
public:
    ApprovalRoute() = default;
    ApprovalRoute(std::string routeId, std::string routeName);
    void appendStep(const ApprovalStep& step);
    bool isFullyApproved() const;
    std::size_t currentStepIndex() const;
    std::vector<ApprovalStep>& getSteps();
    const std::vector<ApprovalStep>& getSteps() const;

private:
    std::string routeId_;
    std::string routeName_;
    std::vector<ApprovalStep> steps_;
};

class WorkflowState {
public:
    WorkflowState() = default;
    WorkflowState(std::string documentId, std::string stageName, int elapsedHours, bool blocked);
    void advanceHours(int hours);
    void moveToStage(const std::string& newStage);
    int getElapsedHours() const;
    const std::string& getStageName() const;
    bool isBlocked() const;

private:
    std::string documentId_;
    std::string stageName_;
    int elapsedHours_{0};
    bool blockedFlag_{false};
};

class WorkflowManager {
public:
    explicit WorkflowManager(std::string managerId);
    void startWorkflow(Document& document, const ApprovalRoute& route);
    void submitApproval(Document& document, const User& user, const std::string& comment);
    std::string applyEscalation(const std::string& documentId, const EscalationRule& rule);
    const WorkflowState& getState(const std::string& documentId) const;

private:
    std::string managerId_;
    std::map<std::string, ApprovalRoute> activeRoutes_;
    std::map<std::string, WorkflowState> states_;
};

}
