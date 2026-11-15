#include "../../include/passengers/Passenger.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

Passenger::Passenger(const std::string& passengerId, const std::string& fullName,
                     int age, bool hasSpecialAssistance, bool isCheckedIn)
    : passengerId_(passengerId), fullName_(fullName), age_(age),
      hasSpecialAssistance_(hasSpecialAssistance), isCheckedIn_(isCheckedIn) {}

void Passenger::verifyTravelDocuments(const Passport& passport, const Visa& visa,
                                      int currentYear) const {
    if (passport.getHolderFullName() != fullName_) {
        throw InvalidPassportException("Passport holder name does not match passenger");
    }
    visa.isValidForTravel(passport, currentYear);
}

void Passenger::completeCheckIn(const Passport& passport, int currentYear) {
    passport.verifyFormat();
    if (!passport.isValidForYear(currentYear)) {
        throw InvalidPassportException("Cannot check in with expired passport");
    }
    isCheckedIn_ = true;
}

double Passenger::calculateTotalBaggageWeight(const BaggageItem& checkedBag,
                                              const HandLuggage& cabinBag) const {
    return passengerId_.empty() ? 0.0 : (checkedBag.getWeightKg() + cabinBag.getWeightKg());
}

void Passenger::addLoyaltyPoints(LoyaltyCard& card, int points) const {
    if (isCheckedIn_) {
        card.accrueMiles(points);
    }
}

const std::string& Passenger::getPassengerId() const { return passengerId_; }
const std::string& Passenger::getFullName() const { return fullName_; }
int Passenger::getAge() const { return age_; }
bool Passenger::getHasSpecialAssistance() const { return hasSpecialAssistance_; }
bool Passenger::getIsCheckedIn() const { return isCheckedIn_; }

}
