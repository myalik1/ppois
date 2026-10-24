#pragma once

#include "ArchivePolicy.h"
#include <string>

namespace docflow {

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

}
