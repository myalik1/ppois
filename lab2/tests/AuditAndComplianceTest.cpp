#include "../include/audit/AuditLogger.h"
#include "../include/audit/ComplianceChecker.h"
#include "../include/audit/ComplianceRule.h"
#include "../include/audit/SecurityIncident.h"
#include "../include/core/User.h"
#include "../include/documents/Document.h"
#include "../include/documents/DocumentVersion.h"
#include "../include/exceptions/WorkflowExceptions.h"
#include "../include/signatures/Certificate.h"
#include "../include/signatures/CryptoHasher.h"
#include "../include/signatures/SignatureService.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(AuditAndComplianceTest, AuditLoggingComplianceAndIncidents) {
    User actor("U1", "Auditor", "a@b.c", "D1", true);
    Certificate cert("C1", "U1", "CA", 100, false);
    Document doc("DOC-88", "RegulatedDoc", "U1", DocumentMetadata(1, 1, "RU", 3));
    doc.addNewVersion(DocumentVersion(1, "U1", "Body v1", "Init"));

    AuditLogger logger("SecAudit", 10);
    logger.recordAction(actor, doc, "CREATE");
    logger.recordAction(actor, doc, "VIEW");
    EXPECT_EQ(logger.countActionsByUser("U1"), 2U);
    logger.clearOldEntries(1);
    EXPECT_EQ(logger.getEntriesCount(), 1U);

    SignatureService sigService("Sig", CryptoHasher("SHA256", "S", 1));
    ComplianceChecker checker("ISOChecker");
    checker.addRule(ComplianceRule("R1", 1, true));

    EXPECT_THROW(checker.verifyDocumentCompliance(doc, sigService), ComplianceViolationException);
    sigService.signDocument(doc, actor, cert, 10);
    EXPECT_NO_THROW(checker.verifyDocumentCompliance(doc, sigService));

    SecurityIncident incident("INC-1", "U9", 9, false);
    EXPECT_TRUE(incident.isCriticalIncident());
    incident.resolveIncident();
    EXPECT_TRUE(incident.isResolved());
    checker.registerIncident(incident);
    EXPECT_EQ(checker.countIncidents(), 1U);
}
