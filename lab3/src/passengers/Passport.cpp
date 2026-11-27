#include "../../include/passengers/Passport.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const std::size_t kMinPassportLength = 6;
const std::size_t kMaxPassportLength = 12;
}

Passport::Passport(const std::string& passportNumber,
                   const std::string& holderFullName,
                   const std::string& nationality,
                   int issueYear,
                   int expiryYear)
    : passportNumber_(passportNumber),
      holderFullName_(holderFullName),
      nationality_(nationality),
      issueYear_(issueYear),
      expiryYear_(expiryYear) {}

bool Passport::isValidForYear(int currentYear) const {
    return currentYear >= issueYear_ && currentYear <= expiryYear_;
}

void Passport::verifyFormat() const {
    if (passportNumber_.length() < kMinPassportLength ||
        passportNumber_.length() > kMaxPassportLength) {
        throw InvalidPassportException("Invalid passport number length");
    }
    if (holderFullName_.empty() || nationality_.empty() || expiryYear_ <= issueYear_) {
        throw InvalidPassportException("Invalid passport holder metadata");
    }
}

int Passport::remainingValidityYears(int currentYear) const {
    if (currentYear > expiryYear_) {
        return 0;
    }
    return expiryYear_ - currentYear;
}

const std::string& Passport::getPassportNumber() const { return passportNumber_; }
const std::string& Passport::getHolderFullName() const { return holderFullName_; }
const std::string& Passport::getNationality() const { return nationality_; }
int Passport::getIssueYear() const { return issueYear_; }
int Passport::getExpiryYear() const { return expiryYear_; }

}
