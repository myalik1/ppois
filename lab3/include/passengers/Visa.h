#pragma once

#include <string>
#include "Passport.h"

namespace airport {

class Visa {
private:
    std::string visaNumber_;
    std::string countryCode_;
    int expiryYear_;
    int maxStayDays_;
    bool isMultipleEntry_;

public:
    Visa(const std::string& visaNumber,
         const std::string& countryCode,
         int expiryYear,
         int maxStayDays,
         bool isMultipleEntry);

    void isValidForTravel(const Passport& passport, int currentYear) const;
    bool validateStayDuration(int plannedDays) const;
    bool matchesDestination(const std::string& destinationCountry) const;

    const std::string& getVisaNumber() const;
    const std::string& getCountryCode() const;
    int getExpiryYear() const;
    int getMaxStayDays() const;
    bool getIsMultipleEntry() const;
};

}
