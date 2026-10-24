#include "../../include/documents/ReportDocument.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

ReportDocument::ReportDocument(Document doc, std::string period, int metricsCount, bool verified)
    : baseDocument_(std::move(doc)),
      reportingPeriod_(std::move(period)),
      metricsCount_(metricsCount),
      verifiedFlag_(verified) {}

void ReportDocument::appendMetricSummary(const std::string& metricLine) {
    if (metricLine.empty()) {
        throw InvalidDocumentDataException("Metric summary cannot be empty");
    }
    metricsCount_ += 1;
}

void ReportDocument::verifyReport(const User& reviewer) {
    if (!reviewer.isActive()) {
        throw UnauthorizedAccessException("Inactive reviewer cannot verify report");
    }
    verifiedFlag_ = true;
    baseDocument_.transitionStatus("VERIFIED");
}

int ReportDocument::getMetricsCount() const {
    return metricsCount_;
}

bool ReportDocument::isVerified() const {
    return verifiedFlag_;
}

}
