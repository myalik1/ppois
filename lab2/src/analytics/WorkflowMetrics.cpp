#include "../../include/analytics/WorkflowMetrics.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

WorkflowMetrics::WorkflowMetrics(int processedCount, int rejectedCount, int totalHours)
    : processedCount_(processedCount),
      rejectedCount_(rejectedCount),
      totalProcessingHours_(totalHours) {}

void WorkflowMetrics::recordCompletion(int hours, bool approved) {
    if (hours < 0) {
        throw InvalidDocumentDataException("Processing hours cannot be negative");
    }
    totalProcessingHours_ += hours;
    if (approved) {
        processedCount_ += 1;
    } else {
        rejectedCount_ += 1;
    }
}

double WorkflowMetrics::calculateAverageHours() const {
    int totalDocs = processedCount_ + rejectedCount_;
    if (totalDocs == 0) {
        return 0.0;
    }
    return static_cast<double>(totalProcessingHours_) / static_cast<double>(totalDocs);
}

int WorkflowMetrics::getProcessedCount() const {
    return processedCount_;
}

}
