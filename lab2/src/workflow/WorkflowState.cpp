#include "../../include/workflow/WorkflowState.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

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

}
