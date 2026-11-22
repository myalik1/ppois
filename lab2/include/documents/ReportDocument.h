#pragma once

#include "../core/User.h"
#include "Document.h"
#include <string>

namespace docflow {

class ReportDocument {
public:
    ReportDocument(Document doc, std::string period, int metricsCount, bool verified);
    void appendMetricSummary(const std::string& metricLine);
    void verifyReport(const User& reviewer);
    int getMetricsCount() const;
    bool isVerified() const;

private:
    Document baseDocument_;
    std::string reportingPeriod_;
    int metricsCount_;
    bool verifiedFlag_;
};

}
