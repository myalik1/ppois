#pragma once
#include <string>
#include "Engine.h"
#include "FuelTank.h"
#include "CabinLayout.h"
#include "AvionicsSystem.h"
#include "LandingGear.h"

namespace airport {

class Aircraft {
private:
    std::string tailNumber_;
    std::string modelName_;
    double emptyWeightKg_;
    double maxTakeoffWeightKg_;
    bool isAirworthy_;

public:
    Aircraft(const std::string& tailNumber,
             const std::string& modelName,
             double emptyWeightKg,
             double maxTakeoffWeightKg,
             bool isAirworthy = true);

    void performPreFlightCheck(const Engine& engine,
                               const AvionicsSystem& avionics,
                               const LandingGear& gear);
    double calculateCurrentTakeoffWeight(const FuelTank& fuelTank, double payloadKg) const;
    bool verifySeatCapacity(const CabinLayout& layout, int requestedPassengers) const;
    void groundAircraft();

    const std::string& getTailNumber() const;
    const std::string& getModelName() const;
    double getEmptyWeightKg() const;
    double getMaxTakeoffWeightKg() const;
    bool getIsAirworthy() const;
};

}
