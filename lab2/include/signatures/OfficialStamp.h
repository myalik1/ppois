#pragma once

#include <string>

namespace docflow {

class OfficialStamp {
public:
    OfficialStamp(std::string code, std::string orgName, std::string regNumber);
    std::string formatStampMark() const;
    bool belongsToOrganization(const std::string& orgName) const;

private:
    std::string stampCode_;
    std::string organizationName_;
    std::string registrationNumber_;
};

}
