#pragma once
#include <string>
#include "Passenger.h"
#include "BaggageTag.h"

namespace airport {

class LostBaggageRecord {
private:
    std::string claimId_;
    std::string passengerId_;
    std::string tagCode_;
    int daysMissing_;
    bool isResolved_;

public:
    LostBaggageRecord(const std::string& claimId, const Passenger& passenger,
                      const BaggageTag& tag, int daysMissing = 1, bool isResolved = false);

    void incrementMissingDays(int additionalDays);
    double calculateCompensation(double dailyAllowanceUsd) const;
    void markFound(BaggageTag& tag);

    const std::string& getClaimId() const;
    const std::string& getPassengerId() const;
    const std::string& getTagCode() const;
    int getDaysMissing() const;
    bool getIsResolved() const;
};

}
