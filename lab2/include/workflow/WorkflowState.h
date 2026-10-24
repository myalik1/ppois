#pragma once

#include <string>

namespace docflow {

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

}
