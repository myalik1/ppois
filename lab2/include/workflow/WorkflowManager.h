#pragma once

#include "../core/User.h"
#include "../documents/Document.h"
#include "ApprovalRoute.h"
#include "EscalationRule.h"
#include "WorkflowState.h"
#include <map>
#include <string>

namespace docflow {

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
