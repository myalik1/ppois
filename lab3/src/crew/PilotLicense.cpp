#include "../../include/crew/PilotLicense.h"

namespace airport {

PilotLicense::PilotLicense(const std::string& licenseNumber,
                           const std::string& aircraftTypeRating,
                           int issueYear,
                           int expiryYear,
                           bool hasInstrumentRating)
    : licenseNumber_(licenseNumber),
      aircraftTypeRating_(aircraftTypeRating),
      issueYear_(issueYear),
      expiryYear_(expiryYear),
      hasInstrumentRating_(hasInstrumentRating) {}

bool PilotLicense::isLicenseValid(int currentYear) const {
    return !licenseNumber_.empty() && currentYear >= issueYear_ && currentYear <= expiryYear_;
}

bool PilotLicense::matchesAircraftModel(const std::string& modelName) const {
    return !modelName.empty() && aircraftTypeRating_ == modelName;
}

void PilotLicense::renewLicense(int additionalYears) {
    if (additionalYears > 0) {
        expiryYear_ += additionalYears;
    }
}

const std::string& PilotLicense::getLicenseNumber() const { return licenseNumber_; }
const std::string& PilotLicense::getAircraftTypeRating() const { return aircraftTypeRating_; }
int PilotLicense::getIssueYear() const { return issueYear_; }
int PilotLicense::getExpiryYear() const { return expiryYear_; }
bool PilotLicense::getHasInstrumentRating() const { return hasInstrumentRating_; }

}
