#pragma once

#include "../core/Department.h"
#include "DepartmentStats.h"
#include "WorkflowMetrics.h"
#include <string>

namespace docflow {

class AnalyticsReporter {
public:
    AnalyticsReporter(std::string reportHeader, bool includeDetails);
    std::string buildMetricsSummary(const WorkflowMetrics& metrics) const;
    std::string buildDepartmentSummary(
        const Department& dept, const DepartmentStats& stats) const;

private:
    std::string reportHeader_;
    bool includeDetails_;
};

}
