#pragma once
#include <string>
#include "../security/SecurityCheckpoint.h"
#include "../security/SecurityBadge.h"

namespace airport {

class SecurityIncident {
private:
    std::string incidentId_;
    std::string description_;
    int severityLevel_;
    bool isResolved_;
    std::string reportingBadgeId_;

public:
    SecurityIncident(const std::string& incidentId,
                     const std::string& description,
                     int severityLevel,
                     const SecurityBadge& reportingOfficer);

    void escalateIncident(SecurityCheckpoint& checkpoint);
    void resolveIncident(SecurityCheckpoint& checkpoint, const SecurityBadge& supervisorBadge);
    bool isHighSeverity() const;

    const std::string& getIncidentId() const;
    const std::string& getDescription() const;
    int getSeverityLevel() const;
    bool getIsResolved() const;
    const std::string& getReportingBadgeId() const;
};

}
