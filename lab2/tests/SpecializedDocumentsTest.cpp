#include "../include/core/Department.h"
#include "../include/core/User.h"
#include "../include/documents/ContractDocument.h"
#include "../include/documents/Document.h"
#include "../include/documents/DocumentMetadata.h"
#include "../include/documents/InvoiceDocument.h"
#include "../include/documents/MemoDocument.h"
#include "../include/documents/OrderDocument.h"
#include "../include/documents/ReportDocument.h"
#include "../include/exceptions/WorkflowExceptions.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(SpecializedDocumentsTest, ContractInvoiceAndOrderOperations) {
    Document base("D1", "Base", "U1", DocumentMetadata(1, 1, "RU", 1));

    ContractDocument contract(base, "Partner LLC", 5000.0, 30);
    contract.prolongContract(15);
    EXPECT_EQ(contract.getExpirationDay(), 45);
    EXPECT_TRUE(contract.isContractValidOnDay(40));
    EXPECT_THROW(contract.prolongContract(-5), InvalidDocumentDataException);

    InvoiceDocument invoice(base, 1000.0, 20.0, false);
    EXPECT_DOUBLE_EQ(invoice.calculateGrossTotal(), 1200.0);
    EXPECT_THROW(invoice.markAsPaid(500.0), InvalidDocumentDataException);
    invoice.markAsPaid(1200.0);
    EXPECT_TRUE(invoice.isPaid());

    Department dept("DEP-FIN", "Finance", "U1", 50);
    OrderDocument order(base, "Execute audit", "DEP-FIN", 10);
    EXPECT_TRUE(order.isEffectiveOn(12));
    EXPECT_TRUE(order.matchesTargetDepartment(dept));
}

TEST(SpecializedDocumentsTest, ReportAndMemoOperations) {
    Document base("D2", "ReportBase", "U1", DocumentMetadata(1, 1, "RU", 1));
    User reviewer("U2", "Reviewer", "rev@b.c", "D1", true);

    ReportDocument report(base, "2026-Q3", 2, false);
    report.appendMetricSummary("SLA compliance 99%");
    report.verifyReport(reviewer);
    EXPECT_EQ(report.getMetricsCount(), 3);
    EXPECT_TRUE(report.isVerified());

    MemoDocument memo(base, "U1", "U2", false);
    memo.escalateUrgency();
    EXPECT_TRUE(memo.isUrgent());
    EXPECT_TRUE(memo.isAddressedTo(reviewer));
}
