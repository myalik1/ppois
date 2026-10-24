#include "../include/exceptions/WorkflowExceptions.h"
#include "../include/storage/StorageAndArchive.h"
#include <gtest/gtest.h>

using namespace docflow;

TEST(StorageAndArchiveTest, RepositoryBackupFolderAndArchivePolicy) {
    StorageLocation loc("L1", "/data", 1000, 0);
    DocumentRepository repo("Repo1", loc);
    Document doc("DOC-5", "ArchiveDoc", "U1", DocumentMetadata(1, 1, "RU", 1));

    repo.saveDocument(doc, 400);
    EXPECT_EQ(repo.countStoredDocuments(), 1U);

    BackupManager backup("BackupNode");
    backup.createBackupSnapshot(repo, "DOC-5");
    EXPECT_TRUE(backup.hasBackupFor("DOC-5"));
    EXPECT_EQ(backup.getSnapshotCount(), 1);

    Folder folder("F1", "Contracts");
    folder.putDocument(doc);
    EXPECT_EQ(folder.countDocuments(), 1U);
    folder.removeDocumentId("DOC-5");
    EXPECT_EQ(folder.countDocuments(), 0U);

    ArchivePolicy policy("Standard5Y", 100, true);
    EXPECT_EQ(policy.estimateStoredSize(200), 100U);
    ArchiveRecord record("AR-1", "DOC-5", 10, "Standard5Y");
    EXPECT_TRUE(record.canRestore(policy, 50));
    EXPECT_FALSE(record.canRestore(policy, 150));

    repo.deleteDocument("DOC-5", 400);
    EXPECT_EQ(repo.countStoredDocuments(), 0U);
}

TEST(StorageAndArchiveTest, StorageLocationExceptions) {
    StorageLocation loc("L1", "/path", 100, 50);
    EXPECT_THROW(loc.allocateSpace(0), StorageCapacityExceededException);
    EXPECT_THROW(loc.allocateSpace(100), StorageCapacityExceededException);

    loc.releaseSpace(200); // Больше чем usedBytes
    EXPECT_EQ(loc.getAvailableBytes(), 100U);
}

TEST(StorageAndArchiveTest, FolderAndRepositoryExceptions) {
    Folder folder("F1", "Docs");
    EXPECT_THROW(folder.putDocument(Document("", "", "", DocumentMetadata())), InvalidDocumentDataException);
    EXPECT_THROW(folder.removeDocumentId("MISSING"), DocumentNotFoundException);

    StorageLocation loc("L2", "/path", 100, 0);
    DocumentRepository repo("R1", loc);
    EXPECT_THROW(repo.findDocument("MISSING"), DocumentNotFoundException);
    EXPECT_THROW(repo.deleteDocument("MISSING", 10), DocumentNotFoundException);
}

TEST(StorageAndArchiveTest, ArchivePolicyExceptions) {
    ArchivePolicy policy("P1", 10, false);
    EXPECT_THROW(policy.isEligibleForDeletion(-5), ArchivePolicyViolationException);

    ArchiveRecord record("AR", "D1", 20, "P1");
    EXPECT_THROW(record.calculateDaysInArchive(10), ArchivePolicyViolationException);
}
