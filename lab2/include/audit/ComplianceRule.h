#pragma once

#include "../documents/Document.h"
#include <cstddef>
#include <string>

namespace docflow {

class ComplianceRule {
public:
    ComplianceRule(std::string ruleCode, std::size_t minVersions, bool requireSignature);
    bool checkVersionCount(const Document& document) const;
    bool evaluateCompliance(const Document& document, std::size_t signatureCount) const;

private:
    std::string ruleCode_;
    std::size_t minVersionsRequired_;
    bool requireSignature_;
};

}
