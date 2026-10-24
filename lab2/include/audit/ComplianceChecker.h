#pragma once

#include "../signatures/SignatureService.h"
#include "ComplianceRule.h"
#include "SecurityIncident.h"
#include <cstddef>
#include <string>
#include <vector>

namespace docflow {

class ComplianceChecker {
public:
    explicit ComplianceChecker(std::string checkerName);
    void addRule(const ComplianceRule& rule);
    void verifyDocumentCompliance(
        const Document& document, const SignatureService& sigService) const;
    void registerIncident(const SecurityIncident& incident);
    std::size_t countIncidents() const;

private:
    std::string checkerName_;
    std::vector<ComplianceRule> rules_;
    std::vector<SecurityIncident> incidents_;
};

}
