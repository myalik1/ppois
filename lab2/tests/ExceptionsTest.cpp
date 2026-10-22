#include "../include/exceptions/WorkflowExceptions.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(ExceptionsTest, AllTwelveCustomExceptionsCarryExpectedCodes) {
    DocumentWorkflowException baseEx("base", 1000);
    InvalidDocumentStateException stateEx("state");
    UnauthorizedAccessException authEx("auth");
    DocumentNotFoundException notFoundEx("notfound");
    SignatureVerificationException sigEx("sig");
    CertificateExpiredException certEx("cert");
    WorkflowRouteException routeEx("route");
    StorageCapacityExceededException storageEx("storage");
    ArchivePolicyViolationException archiveEx("archive");
    InvalidDocumentDataException dataEx("data");
    ComplianceViolationException compEx("comp");
    SlaBreachException slaEx("sla");

    EXPECT_EQ(baseEx.getErrorCode(), 1000);
    EXPECT_EQ(stateEx.getErrorCode(), 1001);
    EXPECT_EQ(authEx.getErrorCode(), 1002);
    EXPECT_EQ(notFoundEx.getErrorCode(), 1003);
    EXPECT_EQ(sigEx.getErrorCode(), 1004);
    EXPECT_EQ(certEx.getErrorCode(), 1005);
    EXPECT_EQ(routeEx.getErrorCode(), 1006);
    EXPECT_EQ(storageEx.getErrorCode(), 1007);
    EXPECT_EQ(archiveEx.getErrorCode(), 1008);
    EXPECT_EQ(dataEx.getErrorCode(), 1009);
    EXPECT_EQ(compEx.getErrorCode(), 1010);
    EXPECT_EQ(slaEx.getErrorCode(), 1011);
}
