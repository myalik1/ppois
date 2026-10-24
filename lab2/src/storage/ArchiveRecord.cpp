#include "../../include/storage/ArchiveRecord.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

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

}
