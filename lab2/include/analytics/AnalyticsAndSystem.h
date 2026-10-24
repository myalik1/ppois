#pragma once

#include "../audit/AuditAndCompliance.h"
#include "../core/IdentityAndAccess.h"
#include "../documents/DocumentCore.h"
#include "../storage/StorageAndArchive.h"
#include "../workflow/WorkflowEngine.h"
#include <cstddef>
#include <string>

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

class DepartmentStats {
public:
    DepartmentStats(std::string departmentId, int createdCount, int archivedCount);
    void registerCreation();
    double calculateActiveRatio() const;

private:
    std::string departmentId_;
    int createdDocsCount_;
    int archivedDocsCount_;
};

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

class DocumentFlowSystem {
public:
    DocumentFlowSystem(
        std::string systemName,
        AccessController accessController,
        DocumentRepository repository,
        WorkflowManager workflowManager,
        AuditLogger auditLogger);
    void registerAndStoreDocument(
        const User& actor, const Document& document, std::size_t sizeBytes);
    void initiateDocumentApproval(
        const User& actor, const std::string& documentId, const ApprovalRoute& route);
    void approveDocumentInSystem(
        const User& actor, const std::string& documentId, const std::string& comment);
    Document getStoredDocument(const std::string& documentId) const;
    std::size_t getAuditCount() const;

private:
    std::string systemName_;
    AccessController accessController_;
    DocumentRepository repository_;
    WorkflowManager workflowManager_;
    AuditLogger auditLogger_;
};

}
