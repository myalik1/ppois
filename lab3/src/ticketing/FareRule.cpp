#include "../../include/ticketing/FareRule.h"

namespace airport {

namespace {
const double kPercentDivisor = 100.0;
}

FareRule::FareRule(const std::string& fareCode,
                   bool isRefundable,
                   double changePenaltyUsd,
                   double freeBaggageAllowanceKg,
                   int milesMultiplierPercent)
    : fareCode_(fareCode),
      isRefundable_(isRefundable),
      changePenaltyUsd_(changePenaltyUsd),
      freeBaggageAllowanceKg_(freeBaggageAllowanceKg),
      milesMultiplierPercent_(milesMultiplierPercent) {}

double FareRule::calculateRefundAmount(double ticketPrice) const {
    if (!isRefundable_ || ticketPrice <= changePenaltyUsd_) {
        return 0.0;
    }
    return ticketPrice - changePenaltyUsd_;
}

double FareRule::calculateChangeCost(double priceDifference) const {
    double diff = priceDifference > 0.0 ? priceDifference : 0.0;
    return changePenaltyUsd_ + diff;
}

int FareRule::computeEarnedMiles(int baseFlightMiles) const {
    if (baseFlightMiles <= 0 || milesMultiplierPercent_ <= 0) {
        return 0;
    }
    return static_cast<int>(baseFlightMiles * (milesMultiplierPercent_ / kPercentDivisor));
}

const std::string& FareRule::getFareCode() const { return fareCode_; }
bool FareRule::getIsRefundable() const { return isRefundable_; }
double FareRule::getChangePenaltyUsd() const { return changePenaltyUsd_; }
double FareRule::getFreeBaggageAllowanceKg() const { return freeBaggageAllowanceKg_; }
int FareRule::getMilesMultiplierPercent() const { return milesMultiplierPercent_; }

}
