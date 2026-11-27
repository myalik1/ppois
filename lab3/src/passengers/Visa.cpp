#include "../../include/passengers/Visa.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

Visa::Visa(const std::string& visaNumber,
           const std::string& countryCode,
           int expiryYear,
           int maxStayDays,
           bool isMultipleEntry)
    : visaNumber_(visaNumber),
      countryCode_(countryCode),
      expiryYear_(expiryYear),
      maxStayDays_(maxStayDays),
      isMultipleEntry_(isMultipleEntry) {}

void Visa::isValidForTravel(const Passport& passport, int currentYear) const {
    passport.verifyFormat();
    if (!passport.isValidForYear(currentYear)) {
        throw InvalidPassportException("Passport expired for visa verification");
    }
    if (currentYear > expiryYear_ || visaNumber_.empty()) {
        throw VisaExpiredException("Visa is expired or empty");
    }
}

bool Visa::validateStayDuration(int plannedDays) const {
    return plannedDays > 0 && plannedDays <= maxStayDays_;
}

bool Visa::matchesDestination(const std::string& destinationCountry) const {
    return countryCode_ == destinationCountry;
}

const std::string& Visa::getVisaNumber() const { return visaNumber_; }
const std::string& Visa::getCountryCode() const { return countryCode_; }
int Visa::getExpiryYear() const { return expiryYear_; }
int Visa::getMaxStayDays() const { return maxStayDays_; }
bool Visa::getIsMultipleEntry() const { return isMultipleEntry_; }

}
