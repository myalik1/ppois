#include "../../include/passengers/BaggageItem.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kAbsoluteMaxBaggageKg = 32.0;
}

BaggageItem::BaggageItem(double weightKg, double lengthCm,
                         double widthCm, double heightCm, bool isFragile)
    : weightKg_(weightKg), lengthCm_(lengthCm), widthCm_(widthCm),
      heightCm_(heightCm), isFragile_(isFragile) {}

double BaggageItem::calculateVolumeCm3() const {
    return lengthCm_ * widthCm_ * heightCm_;
}

void BaggageItem::checkWeightLimit(double maxAllowedKg) const {
    double effectiveLimit = maxAllowedKg < kAbsoluteMaxBaggageKg ? maxAllowedKg : kAbsoluteMaxBaggageKg;
    if (weightKg_ <= 0.0 || weightKg_ > effectiveLimit) {
        throw BaggageOverweightException("Baggage exceeds maximum weight safety limit");
    }
}

double BaggageItem::calculateOverweightFee(double freeAllowanceKg, double ratePerKg) const {
    if (weightKg_ <= freeAllowanceKg || ratePerKg <= 0.0) {
        return 0.0;
    }
    return (weightKg_ - freeAllowanceKg) * ratePerKg;
}

bool BaggageItem::attachTag(BaggageTag& tag) const {
    if (!tag.validateTagFormat()) {
        return false;
    }
    tag.markScanned();
    return true;
}

double BaggageItem::getWeightKg() const { return weightKg_; }
double BaggageItem::getLengthCm() const { return lengthCm_; }
double BaggageItem::getWidthCm() const { return widthCm_; }
double BaggageItem::getHeightCm() const { return heightCm_; }
bool BaggageItem::getIsFragile() const { return isFragile_; }

}
