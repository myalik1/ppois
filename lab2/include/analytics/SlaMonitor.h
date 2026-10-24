#pragma once

#include "../workflow/WorkflowState.h"
#include <string>

namespace docflow {

class SlaMonitor {
public:
    SlaMonitor(std::string slaName, int maxAllowedHours, int breachCounter);
    void checkWorkflowSla(const WorkflowState& state);
    double calculateBreachRate(int totalChecked) const;
    int getBreachCounter() const;

private:
    std::string slaName_;
    int maxAllowedHours_;
    int breachCounter_;
};

}
