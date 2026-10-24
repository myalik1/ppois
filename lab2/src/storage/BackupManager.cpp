#include "../../include/storage/BackupManager.h"
#include <algorithm>

namespace docflow {

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
