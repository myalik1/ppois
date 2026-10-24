#pragma once

namespace docflow {

class WorkflowMetrics {
public:
    WorkflowMetrics(int processedCount, int rejectedCount, int totalHours);
    void recordCompletion(int hours, bool approved);
    double calculateAverageHours() const;
    int getProcessedCount() const;

private:
    int processedCount_;
    int rejectedCount_;
    int totalProcessingHours_;
};

}
