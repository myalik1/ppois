#include "../../include/analytics/AnalyticsAndSystem.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const int kWriteAccessLevel = 2;
}

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

DepartmentStats::DepartmentStats(std::string departmentId, int createdCount, int archivedCount)
    : departmentId_(std::move(departmentId)),
      createdDocsCount_(createdCount),
      archivedDocsCount_(archivedCount) {}

void DepartmentStats::registerCreation() {
    createdDocsCount_ += 1;
}

double DepartmentStats::calculateActiveRatio() const {
    if (createdDocsCount_ <= 0) {
        return 0.0;
    }
    int activeCount = createdDocsCount_ - archivedDocsCount_;
    return static_cast<double>(activeCount) / static_cast<double>(createdDocsCount_);
}

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

DocumentFlowSystem::DocumentFlowSystem(
    std::string systemName,
    AccessController accessController,
    DocumentRepository repository,
    WorkflowManager workflowManager,
    AuditLogger auditLogger)
    : systemName_(std::move(systemName)),
      accessController_(std::move(accessController)),
      repository_(std::move(repository)),
      workflowManager_(std::move(workflowManager)),
      auditLogger_(std::move(auditLogger)) {}

void DocumentFlowSystem::registerAndStoreDocument(
    const User& actor, const Document& document, std::size_t sizeBytes) {
    bool allowed = accessController_.verifyAccess(actor, "DOCUMENT", kWriteAccessLevel);
    if (!allowed) {
        throw UnauthorizedAccessException("User lacks permission to store documents");
    }
    repository_.saveDocument(document, sizeBytes);
    auditLogger_.recordAction(actor, document, "STORE_DOCUMENT");
}

void DocumentFlowSystem::initiateDocumentApproval(
    const User& actor, const std::string& documentId, const ApprovalRoute& route) {
    Document doc = repository_.findDocument(documentId);
    workflowManager_.startWorkflow(doc, route);
    repository_.deleteDocument(documentId, 1);
    repository_.saveDocument(doc, 1);
    auditLogger_.recordAction(actor, doc, "START_WORKFLOW");
}

void DocumentFlowSystem::approveDocumentInSystem(
    const User& actor, const std::string& documentId, const std::string& comment) {
    Document doc = repository_.findDocument(documentId);
    workflowManager_.submitApproval(doc, actor, comment);
    repository_.deleteDocument(documentId, 1);
    repository_.saveDocument(doc, 1);
    auditLogger_.recordAction(actor, doc, "APPROVE_DOCUMENT");
}

Document DocumentFlowSystem::getStoredDocument(const std::string& documentId) const {
    return repository_.findDocument(documentId);
}

std::size_t DocumentFlowSystem::getAuditCount() const {
    return auditLogger_.getEntriesCount();
}

}
