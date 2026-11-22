#include "../../include/audit/SecurityIncident.h"

namespace docflow {

namespace {
const int kCriticalSeverityThreshold = 8;
}

SecurityIncident::SecurityIncident(
    std::string id, std::string offenderId, int severityScore, bool resolved)
    : incidentId_(std::move(id)),
      offenderUserId_(std::move(offenderId)),
      severityScore_(severityScore),
      resolvedFlag_(resolved) {}

void SecurityIncident::resolveIncident() {
    resolvedFlag_ = true;
}

bool SecurityIncident::isCriticalIncident() const {
    return severityScore_ >= kCriticalSeverityThreshold;
}

bool SecurityIncident::isResolved() const {
    return resolvedFlag_;
}

}
