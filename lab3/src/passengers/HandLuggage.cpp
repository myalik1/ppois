#include "../../include/passengers/HandLuggage.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const int kMaxAllowedLiquidMl = 100;
}

HandLuggage::HandLuggage(double weightKg, bool containsLiquids,
                         int liquidVolumeMl, bool fitsUnderSeat)
    : weightKg_(weightKg), containsLiquids_(containsLiquids),
      liquidVolumeMl_(liquidVolumeMl), fitsUnderSeat_(fitsUnderSeat) {}

bool HandLuggage::validateCabinCompliance(double maxCabinWeightKg) const {
    return weightKg_ > 0.0 && weightKg_ <= maxCabinWeightKg;
}

void HandLuggage::checkLiquidRules() const {
    if (containsLiquids_ && liquidVolumeMl_ > kMaxAllowedLiquidMl) {
        throw SecurityBreachException("Cabin liquid volume exceeds 100ml limit");
    }
}

bool HandLuggage::inspectLuggage(double maxCabinWeightKg) const {
    checkLiquidRules();
    return validateCabinCompliance(maxCabinWeightKg);
}

double HandLuggage::getWeightKg() const { return weightKg_; }
bool HandLuggage::getContainsLiquids() const { return containsLiquids_; }
int HandLuggage::getLiquidVolumeMl() const { return liquidVolumeMl_; }
bool HandLuggage::getFitsUnderSeat() const { return fitsUnderSeat_; }

}
