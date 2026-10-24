#pragma once

#include "ApprovalStep.h"
#include <cstddef>
#include <string>
#include <vector>

namespace docflow {

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

}
