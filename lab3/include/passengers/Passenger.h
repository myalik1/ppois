#pragma once
#include <string>
#include "Passport.h"
#include "Visa.h"
#include "LoyaltyCard.h"
#include "BaggageItem.h"
#include "HandLuggage.h"

namespace airport {

class Passenger {
private:
    std::string passengerId_;
    std::string fullName_;
    int age_;
    bool hasSpecialAssistance_;
    bool isCheckedIn_;

public:
    Passenger(const std::string& passengerId, const std::string& fullName,
              int age, bool hasSpecialAssistance, bool isCheckedIn = false);

    void verifyTravelDocuments(const Passport& passport, const Visa& visa, int currentYear) const;
    void completeCheckIn(const Passport& passport, int currentYear);
    double calculateTotalBaggageWeight(const BaggageItem& checkedBag,
                                       const HandLuggage& cabinBag) const;
    void addLoyaltyPoints(LoyaltyCard& card, int points) const;

    const std::string& getPassengerId() const;
    const std::string& getFullName() const;
    int getAge() const;
    bool getHasSpecialAssistance() const;
    bool getIsCheckedIn() const;
};

}
