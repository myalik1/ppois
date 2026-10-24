#include "../include/analytics/AnalyticsAndSystem.h"
#include "../include/exceptions/WorkflowExceptions.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(AnalyticsAndSystemTest, MetricsSlaReporterAndSystemFacade) {
    WorkflowMetrics metrics(0, 0, 0);
    metrics.recordCompletion(10, true);
    metrics.recordCompletion(20, false);
    EXPECT_DOUBLE_EQ(metrics.calculateAverageHours(), 15.0);

    Department dept("D1", "IT", "U1", 100);
    DepartmentStats stats("D1", 9, 3);
    stats.registerCreation();
    EXPECT_DOUBLE_EQ(stats.calculateActiveRatio(), 0.7);

    SlaMonitor monitor("StandardSLA", 24, 0);
    WorkflowState overdueState("DOC-1", "IN_REVIEW", 30, false);
    EXPECT_THROW(monitor.checkWorkflowSla(overdueState), SlaBreachException);
    EXPECT_DOUBLE_EQ(monitor.calculateBreachRate(2), 0.5);

    AnalyticsReporter reporter("MonthlyReport", true);
    EXPECT_FALSE(reporter.buildMetricsSummary(metrics).empty());
    EXPECT_FALSE(reporter.buildDepartmentSummary(dept, stats).empty());

    User user("U1", "Admin", "a@b.c", "D1", true);
    Role role("Admin", 10);
    role.addPermission(Permission("P1", "DOCUMENT", 5));
    AccessController ac("AC", true);
    ac.assignRole(user, role);

    DocumentFlowSystem sys(
        "DocFlow",
        ac,
        DocumentRepository("R", StorageLocation("L", "/", 10000, 0)),
        WorkflowManager("WM"),
        AuditLogger("AL", 100));

    Document doc("DOC-100", "SystemDoc", "U1", DocumentMetadata(1, 1, "RU", 2));
    sys.registerAndStoreDocument(user, doc, 100);

    ApprovalRoute route("RT", "FastTrack");
    route.appendStep(ApprovalStep(1, "U1"));
    sys.initiateDocumentApproval(user, "DOC-100", route);
    sys.approveDocumentInSystem(user, "DOC-100", "LGTM");

    Document approved = sys.getStoredDocument("DOC-100");
    EXPECT_EQ(approved.getStatus(), "APPROVED");
    EXPECT_EQ(sys.getAuditCount(), 3U);
}

TEST(AnalyticsAndSystemTest, AnalyticsZeroDivisionAndFormatting) {
    WorkflowMetrics metrics(0, 0, 0);
    EXPECT_DOUBLE_EQ(metrics.calculateAverageHours(), 0.0);
    EXPECT_THROW(metrics.recordCompletion(-5, true), InvalidDocumentDataException);

    DepartmentStats stats("D1", 0, 0);
    EXPECT_DOUBLE_EQ(stats.calculateActiveRatio(), 0.0);

    SlaMonitor sla("S1", 10, 5);
    EXPECT_DOUBLE_EQ(sla.calculateBreachRate(0), 0.0);

    AnalyticsReporter reporter("Header", false);
    EXPECT_EQ(reporter.buildMetricsSummary(metrics), "Header");
}

TEST(AnalyticsAndSystemTest, SystemFacadeExceptions) {
    AccessController ac("AC", true);
    DocumentFlowSystem sys("Sys", ac, DocumentRepository("R", StorageLocation("L", "/", 100, 0)), WorkflowManager("W"), AuditLogger("A", 10));

    User guest("U2", "Guest", "g@b.c", "D1", true);
    Document doc("D1", "T", "U2", DocumentMetadata());
    EXPECT_THROW(sys.registerAndStoreDocument(guest, doc, 10), UnauthorizedAccessException);
}
