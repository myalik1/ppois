#pragma once
#include <string>
#include "../passengers/Passenger.h"
#include "../passengers/Passport.h"
#include "../passengers/Visa.h"
#include "SecurityBadge.h"

namespace airport {

class BorderControl {
private:
    std::string boothNumber_;
    std::string countryCode_;
    int processedTravelersCount_;
    bool isBiometricGateActive_;

public:
    BorderControl(const std::string& boothNumber,
                  const std::string& countryCode,
                  bool isBiometricGateActive = true);

    bool verifyEntryClearance(const Passenger& passenger,
                              const Passport& passport,
                              const Visa& visa,
                              const SecurityBadge& officerBadge,
                              int currentYear);
    void toggleBiometricGate(bool active);
    bool isVisaRequiredForNationality(const Passport& passport) const;

    const std::string& getBoothNumber() const;
    const std::string& getCountryCode() const;
    int getProcessedTravelersCount() const;
    bool getIsBiometricGateActive() const;
};

}
