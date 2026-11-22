#pragma once

#include "../include/analytics/DepartmentStats.h"
#include "../include/analytics/DocumentFlowSystem.h"
#include "../include/analytics/SlaMonitor.h"
#include "../include/analytics/WorkflowMetrics.h"
#include "../include/audit/ComplianceChecker.h"
#include "../include/core/AccessController.h"
#include "../include/core/Department.h"
#include "../include/core/User.h"
#include "../include/notifications/NotificationService.h"
#include "../include/search/SearchEngine.h"
#include "../include/search/TagRegistry.h"
#include "../include/signatures/Certificate.h"
#include "../include/signatures/SignatureService.h"
#include "../include/storage/BackupManager.h"
#include "../include/storage/Folder.h"
#include <iostream>

namespace docflow {

class ConsoleMenu {
public:
    ConsoleMenu();
    void runInteractiveLoop(std::istream& input, std::ostream& output);

private:
    void initializeDefaultConfiguration();
    void printMenu(std::ostream& output) const;
    void dispatchChoice(int choice, std::istream& input, std::ostream& output);
    void executeDocumentAndWorkflowCommand(int choice, std::istream& input, std::ostream& output);
    void executeInfrastructureCommand(int choice, std::istream& input, std::ostream& output);

    void handleCreateDocument(std::istream& input, std::ostream& output);
    void handleTemplateAndAccess(std::istream& input, std::ostream& output);
    void handleSpecializedDocuments(std::istream& input, std::ostream& output);
    void handleWorkflowAndApproval(std::istream& input, std::ostream& output);
    void handleSignAndStamp(std::istream& input, std::ostream& output);
    void handleStorageAndArchive(std::istream& input, std::ostream& output);
    void handleSearchAndSort(std::istream& input, std::ostream& output);
    void handleNotificationsAndReminders(std::istream& input, std::ostream& output);
    void handleAuditAndCompliance(std::istream& input, std::ostream& output);
    void handleAnalyticsAndStatus(std::istream& input, std::ostream& output);

    Department defaultDepartment_;
    User defaultUser_;
    AccessController accessController_;
    Certificate defaultCert_;
    SignatureService signatureService_;
    Folder activeFolder_;
    BackupManager backupManager_;
    TagRegistry tagRegistry_;
    SearchEngine searchEngine_;
    NotificationService notificationService_;
    ComplianceChecker complianceChecker_;
    WorkflowMetrics workflowMetrics_;
    DepartmentStats departmentStats_;
    SlaMonitor slaMonitor_;
    DocumentFlowSystem system_;
};

}
