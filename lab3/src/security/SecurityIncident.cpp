#include "../../include/security/SecurityIncident.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const int kHighSeverityThreshold = 4;
const int kSupervisorClearanceLevel = 4;
}

SecurityIncident::SecurityIncident(const std::string& incidentId,
                                   const std::string& description,
                                   int severityLevel,
                                   const SecurityBadge& reportingOfficer)
    : incidentId_(incidentId),
      description_(description),
      severityLevel_(severityLevel),
      isResolved_(false),
      reportingBadgeId_(reportingOfficer.getBadgeId()) {}

void SecurityIncident::escalateIncident(SecurityCheckpoint& checkpoint) {
    ++severityLevel_;
    if (isHighSeverity()) {
        checkpoint.triggerLockdown();
    }
}

void SecurityIncident::resolveIncident(SecurityCheckpoint& checkpoint,
                                       const SecurityBadge& supervisorBadge) {
    if (!supervisorBadge.verifyAccessZone(kSupervisorClearanceLevel)) {
        throw SecurityBreachException("Supervisor clearance required to resolve incident");
    }
    checkpoint.liftLockdown();
    isResolved_ = true;
}

bool SecurityIncident::isHighSeverity() const {
    return severityLevel_ >= kHighSeverityThreshold;
}

const std::string& SecurityIncident::getIncidentId() const { return incidentId_; }
const std::string& SecurityIncident::getDescription() const { return description_; }
int SecurityIncident::getSeverityLevel() const { return severityLevel_; }
bool SecurityIncident::getIsResolved() const { return isResolved_; }
const std::string& SecurityIncident::getReportingBadgeId() const { return reportingBadgeId_; }

}
