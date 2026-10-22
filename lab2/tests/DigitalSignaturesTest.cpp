#include "../include/exceptions/WorkflowExceptions.h"
#include "../include/signatures/DigitalSignatures.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(DigitalSignaturesTest, SigningVerificationAndStampFormatting) {
    User signer("U1", "Signer", "s@b.c", "D1", true);
    Certificate cert("SN-01", "U1", "RootCA", 100, false);
    Document doc("DOC-77", "Contract", "U1", DocumentMetadata(1, 1, "RU", 2));

    CryptoHasher hasher("SHA256", "SALT", 5);
    SignatureService service("SigSvc", hasher);

    DigitalSignature sig = service.signDocument(doc, signer, cert, 50);
    EXPECT_TRUE(sig.matchesDocument(doc));
    EXPECT_TRUE(sig.validateHashFormat());
    EXPECT_EQ(service.countSignatures("DOC-77"), 1U);
    EXPECT_TRUE(service.verifyDocumentSignatures(doc, cert, 50));

    cert.revokeCertificate();
    EXPECT_THROW(service.signDocument(doc, signer, cert, 50), CertificateExpiredException);

    OfficialStamp stamp("ST-1", "BSUIR", "REG-99");
    EXPECT_TRUE(stamp.belongsToOrganization("BSUIR"));
    EXPECT_FALSE(stamp.formatStampMark().empty());
}
