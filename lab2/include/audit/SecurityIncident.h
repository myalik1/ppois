#pragma once

#include <string>

namespace docflow {

class SecurityIncident {
public:
    SecurityIncident(std::string id, std::string offenderId, int severityScore, bool resolved);
    void resolveIncident();
    bool isCriticalIncident() const;
    bool isResolved() const;

private:
    std::string incidentId_;
    std::string offenderUserId_;
    int severityScore_;
    bool resolvedFlag_;
};

}
