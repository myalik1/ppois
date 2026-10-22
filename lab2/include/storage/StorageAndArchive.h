#pragma once

#include "../documents/DocumentCore.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace docflow {

class StorageLocation {
public:
    StorageLocation(std::string id, std::string rootPath, std::size_t capacity, std::size_t used);
    void allocateSpace(std::size_t bytes);
    void releaseSpace(std::size_t bytes);
    std::size_t getAvailableBytes() const;

private:
    std::string locationId_;
    std::string rootPath_;
    std::size_t capacityBytes_;
    std::size_t usedBytes_;
};

class Folder {
public:
    Folder(std::string folderId, std::string folderName);
    void putDocument(const Document& document);
    void removeDocumentId(const std::string& documentId);
    std::size_t countDocuments() const;

private:
    std::string folderId_;
    std::string folderName_;
    std::vector<std::string> documentIds_;
};

class ArchivePolicy {
public:
    ArchivePolicy(std::string policyName, int retentionDays, bool compressionEnabled);
    bool isEligibleForDeletion(int archivedDays) const;
    std::size_t estimateStoredSize(std::size_t rawSize) const;
    const std::string& getPolicyName() const;

private:
    std::string policyName_;
    int retentionDays_;
    bool compressionEnabled_;
};

class ArchiveRecord {
public:
    ArchiveRecord(std::string recordId, std::string docId, int archivedOnDay, std::string policy);
    int calculateDaysInArchive(int currentDay) const;
    bool canRestore(const ArchivePolicy& policy, int currentDay) const;

private:
    std::string recordId_;
    std::string documentId_;
    int archivedOnDay_;
    std::string policyName_;
};

class DocumentRepository {
public:
    DocumentRepository(std::string name, StorageLocation location);
    void saveDocument(const Document& document, std::size_t sizeBytes);
    Document findDocument(const std::string& documentId) const;
    void deleteDocument(const std::string& documentId, std::size_t sizeBytes);
    std::size_t countStoredDocuments() const;

private:
    std::string repositoryName_;
    StorageLocation location_;
    std::map<std::string, Document> documents_;
};

class BackupManager {
public:
    explicit BackupManager(std::string backupNodeName);
    void createBackupSnapshot(
        const DocumentRepository& repository, const std::string& documentId);
    bool hasBackupFor(const std::string& documentId) const;
    int getSnapshotCount() const;

private:
    std::string backupNodeName_;
    int snapshotCount_{0};
    std::vector<std::string> backedUpIds_;
};

}
