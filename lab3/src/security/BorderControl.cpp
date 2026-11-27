#include "../../include/security/BorderControl.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const int kMinBorderOfficerClearance = 2;
}

BorderControl::BorderControl(const std::string& boothNumber,
                             const std::string& countryCode,
                             bool isBiometricGateActive)
    : boothNumber_(boothNumber),
      countryCode_(countryCode),
      processedTravelersCount_(0),
      isBiometricGateActive_(isBiometricGateActive) {}

bool BorderControl::verifyEntryClearance(const Passenger& passenger,
                                         const Passport& passport,
                                         const Visa& visa,
                                         const SecurityBadge& officerBadge,
                                         int currentYear) {
    if (!officerBadge.verifyAccessZone(kMinBorderOfficerClearance)) {
        throw SecurityBreachException("Unauthorized officer at border control booth");
    }
    passenger.verifyTravelDocuments(passport, visa, currentYear);
    if (isVisaRequiredForNationality(passport) && !visa.matchesDestination(countryCode_)) {
        throw VisaExpiredException("Visa country code does not match border control country");
    }
    ++processedTravelersCount_;
    return true;
}

void BorderControl::toggleBiometricGate(bool active) {
    isBiometricGateActive_ = active;
}

bool BorderControl::isVisaRequiredForNationality(const Passport& passport) const {
    return passport.getNationality() != countryCode_;
}

const std::string& BorderControl::getBoothNumber() const { return boothNumber_; }
const std::string& BorderControl::getCountryCode() const { return countryCode_; }
int BorderControl::getProcessedTravelersCount() const { return processedTravelersCount_; }
bool BorderControl::getIsBiometricGateActive() const { return isBiometricGateActive_; }

}
