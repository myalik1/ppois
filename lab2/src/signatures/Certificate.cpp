#include "../../include/signatures/Certificate.h"

namespace docflow {

Certificate::Certificate(
    std::string serial, std::string holderUserId, std::string issuer, int validUntil, bool revoked)
    : serialNumber_(std::move(serial)),
      holderUserId_(std::move(holderUserId)),
      issuerName_(std::move(issuer)),
      validUntilDay_(validUntil),
      revokedFlag_(revoked) {}

void Certificate::revokeCertificate() {
    revokedFlag_ = true;
}

bool Certificate::isValidForUser(const User& user, int currentDay) const {
    if (revokedFlag_ || currentDay > validUntilDay_) {
        return false;
    }
    const std::string& uid = user.getUserId();
    return holderUserId_ == uid;
}

const std::string& Certificate::getSerialNumber() const {
    return serialNumber_;
}

}
