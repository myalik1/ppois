#pragma once

#include "../core/User.h"
#include <string>

namespace docflow {

class Certificate {
public:
    Certificate(
        std::string serial, std::string holderUserId, std::string issuer, int validUntil, bool revoked);
    void revokeCertificate();
    bool isValidForUser(const User& user, int currentDay) const;
    const std::string& getSerialNumber() const;

private:
    std::string serialNumber_;
    std::string holderUserId_;
    std::string issuerName_;
    int validUntilDay_;
    bool revokedFlag_;
};

}
