#include "../../include/analytics/SlaMonitor.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

SlaMonitor::SlaMonitor(std::string slaName, int maxAllowedHours, int breachCounter)
    : slaName_(std::move(slaName)),
      maxAllowedHours_(maxAllowedHours),
      breachCounter_(breachCounter) {}

void SlaMonitor::checkWorkflowSla(const WorkflowState& state) {
    int elapsed = state.getElapsedHours();
    if (elapsed > maxAllowedHours_) {
        breachCounter_ += 1;
        throw SlaBreachException("Workflow SLA maximum duration breached");
    }
}

double SlaMonitor::calculateBreachRate(int totalChecked) const {
    if (totalChecked <= 0) {
        return 0.0;
    }
    return static_cast<double>(breachCounter_) / static_cast<double>(totalChecked);
}

int SlaMonitor::getBreachCounter() const {
    return breachCounter_;
}

}
