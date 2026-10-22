#include "../include/documents/DocumentCore.h"
#include "../include/exceptions/WorkflowExceptions.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(DocumentCoreTest, TagAttachmentAndMetadataBehaviors) {
    Tag secretTag("Secret", "Security", 8);
    EXPECT_TRUE(secretTag.isHighConfidentiality());
    EXPECT_TRUE(secretTag.matchesCategory("Security"));

    Attachment pdf("contract.pdf", "application/pdf", 1024, "ABC123HASH");
    EXPECT_TRUE(pdf.verifyChecksum("ABC123HASH"));
    EXPECT_TRUE(pdf.exceedsSizeLimit(512));

    DocumentMetadata meta(100, 120, "RU", 2);
    meta.updateModificationTime(200);
    meta.escalateSecurityLevel(3);
    EXPECT_EQ(meta.getSecurityLevel(), 5);
    EXPECT_EQ(meta.getModifiedTimestamp(), 200);
    EXPECT_THROW(meta.updateModificationTime(50), InvalidDocumentDataException);
    EXPECT_THROW(meta.escalateSecurityLevel(10), InvalidDocumentDataException);
}

TEST(DocumentCoreTest, DocumentAndTemplateInstantiation) {
    User author("U1", "Author", "a@b.c", "D1", true);
    DocumentTemplate tmpl("T1", "OrderTemplate", "Order {{NUMBER}} body", 3);
    EXPECT_TRUE(tmpl.validatePlaceholder("{{NUMBER}}"));

    Document doc = tmpl.instantiateDocument("DOC-1", "Order #1", author);
    EXPECT_EQ(doc.getVersions().size(), 1U);
    EXPECT_TRUE(doc.getVersions()[0].containsKeyword("Order"));
    EXPECT_GT(doc.getVersions()[0].calculateContentLength(), 0U);

    doc.attachFile(Attachment("scan.png", "image/png", 200, "H1"));
    doc.applyTag(Tag("Internal", "General", 2));
    doc.transitionStatus("ARCHIVED");
    EXPECT_THROW(doc.addNewVersion(DocumentVersion(2, "U1", "New", "Upd")),
                 InvalidDocumentStateException);
}
