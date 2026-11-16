#pragma once

#include <cstddef>
#include <string>

namespace docflow {

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

}
