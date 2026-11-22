#pragma once

#include "DocumentRepository.h"
#include <string>
#include <vector>

namespace docflow {

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
