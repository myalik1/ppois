#include "../../include/storage/StorageAndArchive.h"
#include "../../include/exceptions/WorkflowExceptions.h"
#include <algorithm>

namespace docflow {

namespace {
const std::size_t kCompressionDivisor = 2;
}

StorageLocation::StorageLocation(
    std::string id, std::string rootPath, std::size_t capacity, std::size_t used)
    : locationId_(std::move(id)),
      rootPath_(std::move(rootPath)),
      capacityBytes_(capacity),
      usedBytes_(used) {}

void StorageLocation::allocateSpace(std::size_t bytes) {
    if (bytes == 0 || usedBytes_ + bytes > capacityBytes_) {
        throw StorageCapacityExceededException("Not enough storage capacity");
    }
    usedBytes_ += bytes;
}

void StorageLocation::releaseSpace(std::size_t bytes) {
    if (bytes > usedBytes_) {
        usedBytes_ = 0;
        return;
    }
    usedBytes_ -= bytes;
}

std::size_t StorageLocation::getAvailableBytes() const {
    return capacityBytes_ - usedBytes_;
}

Folder::Folder(std::string folderId, std::string folderName)
    : folderId_(std::move(folderId)), folderName_(std::move(folderName)) {}

void Folder::putDocument(const Document& document) {
    const std::string& docId = document.getDocumentId();
    if (docId.empty()) {
        throw InvalidDocumentDataException("Cannot put document with empty ID into folder");
    }
    documentIds_.push_back(docId);
}

void Folder::removeDocumentId(const std::string& documentId) {
    auto it = std::find(documentIds_.begin(), documentIds_.end(), documentId);
    if (it == documentIds_.end()) {
        throw DocumentNotFoundException("Document ID not found in folder");
    }
    documentIds_.erase(it);
}

std::size_t Folder::countDocuments() const {
    return documentIds_.size();
}

ArchivePolicy::ArchivePolicy(std::string policyName, int retentionDays, bool compressionEnabled)
    : policyName_(std::move(policyName)),
      retentionDays_(retentionDays),
      compressionEnabled_(compressionEnabled) {}

bool ArchivePolicy::isEligibleForDeletion(int archivedDays) const {
    if (archivedDays < 0) {
        throw ArchivePolicyViolationException("Archived days cannot be negative");
    }
    return archivedDays >= retentionDays_;
}

std::size_t ArchivePolicy::estimateStoredSize(std::size_t rawSize) const {
    if (compressionEnabled_) {
        return rawSize / kCompressionDivisor;
    }
    return rawSize;
}

const std::string& ArchivePolicy::getPolicyName() const {
    return policyName_;
}

ArchiveRecord::ArchiveRecord(
    std::string recordId, std::string docId, int archivedOnDay, std::string policy)
    : recordId_(std::move(recordId)),
      documentId_(std::move(docId)),
      archivedOnDay_(archivedOnDay),
      policyName_(std::move(policy)) {}

int ArchiveRecord::calculateDaysInArchive(int currentDay) const {
    if (currentDay < archivedOnDay_) {
        throw ArchivePolicyViolationException("Current day precedes archive date");
    }
    return currentDay - archivedOnDay_;
}

bool ArchiveRecord::canRestore(const ArchivePolicy& policy, int currentDay) const {
    int daysInArchive = calculateDaysInArchive(currentDay);
    bool expired = policy.isEligibleForDeletion(daysInArchive);
    return !expired && policyName_ == policy.getPolicyName();
}

DocumentRepository::DocumentRepository(std::string name, StorageLocation location)
    : repositoryName_(std::move(name)), location_(std::move(location)) {}

void DocumentRepository::saveDocument(const Document& document, std::size_t sizeBytes) {
    const std::string& docId = document.getDocumentId();
    if (docId.empty()) {
        throw InvalidDocumentDataException("Document ID cannot be empty when saving");
    }
    location_.allocateSpace(sizeBytes);
    documents_[docId] = document;
}

Document DocumentRepository::findDocument(const std::string& documentId) const {
    auto it = documents_.find(documentId);
    if (it == documents_.end()) {
        throw DocumentNotFoundException("Document not found in repository");
    }
    return it->second;
}

void DocumentRepository::deleteDocument(const std::string& documentId, std::size_t sizeBytes) {
    auto it = documents_.find(documentId);
    if (it == documents_.end()) {
        throw DocumentNotFoundException("Cannot delete missing document");
    }
    documents_.erase(it);
    location_.releaseSpace(sizeBytes);
}

std::size_t DocumentRepository::countStoredDocuments() const {
    return documents_.size();
}

BackupManager::BackupManager(std::string backupNodeName)
    : backupNodeName_(std::move(backupNodeName)) {}

void BackupManager::createBackupSnapshot(
    const DocumentRepository& repository, const std::string& documentId) {
    Document found = repository.findDocument(documentId);
    backedUpIds_.push_back(found.getDocumentId());
    snapshotCount_ += 1;
}

bool BackupManager::hasBackupFor(const std::string& documentId) const {
    return std::find(backedUpIds_.begin(), backedUpIds_.end(), documentId) != backedUpIds_.end();
}

int BackupManager::getSnapshotCount() const {
    return snapshotCount_;
}

}
