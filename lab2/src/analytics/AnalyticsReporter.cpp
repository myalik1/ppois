#include "../../include/analytics/AnalyticsReporter.h"

namespace docflow {

AnalyticsReporter::AnalyticsReporter(std::string reportHeader, bool includeDetails)
    : reportHeader_(std::move(reportHeader)), includeDetails_(includeDetails) {}

std::string AnalyticsReporter::buildMetricsSummary(const WorkflowMetrics& metrics) const {
    int processed = metrics.getProcessedCount();
    if (!includeDetails_) {
        return reportHeader_;
    }
    return reportHeader_ + " | Processed=" + std::to_string(processed);
}

std::string AnalyticsReporter::buildDepartmentSummary(
    const Department& dept, const DepartmentStats& stats) const {
    double ratio = stats.calculateActiveRatio();
    return dept.getDepartmentName() + ":Ratio=" + std::to_string(ratio);
}

}
