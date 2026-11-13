#pragma once
namespace airport {

class HandLuggage {
private:
    double weightKg_;
    bool containsLiquids_;
    int liquidVolumeMl_;
    bool fitsUnderSeat_;

public:
    HandLuggage(double weightKg, bool containsLiquids,
                int liquidVolumeMl, bool fitsUnderSeat);

    bool validateCabinCompliance(double maxCabinWeightKg) const;
    void checkLiquidRules() const;
    bool inspectLuggage(double maxCabinWeightKg) const;

    double getWeightKg() const;
    bool getContainsLiquids() const;
    int getLiquidVolumeMl() const;
    bool getFitsUnderSeat() const;
};

}
