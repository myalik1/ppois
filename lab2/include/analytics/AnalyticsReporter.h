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
    static std::string buildDepartmentSummary(
        const Department& dept, const DepartmentStats& stats);

private:
    std::string reportHeader_;
    bool includeDetails_;
};

}
