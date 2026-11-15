#pragma once
#include "BaggageTag.h"

namespace airport {

class BaggageItem {
private:
    double weightKg_;
    double lengthCm_;
    double widthCm_;
    double heightCm_;
    bool isFragile_;

public:
    BaggageItem(double weightKg,
                double lengthCm,
                double widthCm,
                double heightCm,
                bool isFragile);

    double calculateVolumeCm3() const;
    void checkWeightLimit(double maxAllowedKg) const;
    double calculateOverweightFee(double freeAllowanceKg, double ratePerKg) const;
    bool attachTag(BaggageTag& tag) const;

    double getWeightKg() const;
    double getLengthCm() const;
    double getWidthCm() const;
    double getHeightCm() const;
    bool getIsFragile() const;
};

}
