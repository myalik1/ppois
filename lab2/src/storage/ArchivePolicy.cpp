#include "../../include/storage/ArchivePolicy.h"
#include "../../include/exceptions/WorkflowExceptions.h"

namespace docflow {

namespace {
const std::size_t kCompressionDivisor = 2;
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

}
