#pragma once
#include <string>

namespace airport {

class FareRule {
private:
    std::string fareCode_;
    bool isRefundable_;
    double changePenaltyUsd_;
    double freeBaggageAllowanceKg_;
    int milesMultiplierPercent_;

public:
    FareRule(const std::string& fareCode,
             bool isRefundable,
             double changePenaltyUsd,
             double freeBaggageAllowanceKg,
             int milesMultiplierPercent);

    double calculateRefundAmount(double ticketPrice) const;
    double calculateChangeCost(double priceDifference) const;
    int computeEarnedMiles(int baseFlightMiles) const;

    const std::string& getFareCode() const;
    bool getIsRefundable() const;
    double getChangePenaltyUsd() const;
    double getFreeBaggageAllowanceKg() const;
    int getMilesMultiplierPercent() const;
};

}
