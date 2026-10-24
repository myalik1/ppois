#include "../../include/signatures/OfficialStamp.h"

namespace docflow {

OfficialStamp::OfficialStamp(std::string code, std::string orgName, std::string regNumber)
    : stampCode_(std::move(code)),
      organizationName_(std::move(orgName)),
      registrationNumber_(std::move(regNumber)) {}

std::string OfficialStamp::formatStampMark() const {
    return "[" + stampCode_ + "|" + organizationName_ + "|" + registrationNumber_ + "]";
}

bool OfficialStamp::belongsToOrganization(const std::string& orgName) const {
    return organizationName_ == orgName;
}

}
