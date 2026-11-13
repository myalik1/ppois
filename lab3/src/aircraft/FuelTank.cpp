#include "../../include/aircraft/FuelTank.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kSafetyReserveFactor = 1.1;
}

FuelTank::FuelTank(double capacityLiters,
                   double currentLevelLiters,
                   bool isValveOpen,
                   double fuelDensityKgPerL)
    : capacityLiters_(capacityLiters),
      currentLevelLiters_(currentLevelLiters),
      isValveOpen_(isValveOpen),
      fuelDensityKgPerL_(fuelDensityKgPerL) {}

double FuelTank::refuel(double litersToAdd) {
    if (litersToAdd <= 0.0) {
        return 0.0;
    }
    isValveOpen_ = true;
    double availableSpace = capacityLiters_ - currentLevelLiters_;
    double actualAdded = litersToAdd > availableSpace ? availableSpace : litersToAdd;
    currentLevelLiters_ += actualAdded;
    isValveOpen_ = false;
    return actualAdded;
}

void FuelTank::consumeFuel(double litersToBurn) {
    if (litersToBurn > currentLevelLiters_ || litersToBurn < 0.0) {
        throw InsufficientFuelException("Not enough fuel in tank to burn requested volume");
    }
    currentLevelLiters_ -= litersToBurn;
}

double FuelTank::calculateFuelMassKg() const {
    return currentLevelLiters_ * fuelDensityKgPerL_;
}

bool FuelTank::hasSufficientFuel(double requiredLiters) const {
    return currentLevelLiters_ >= requiredLiters * kSafetyReserveFactor;
}

double FuelTank::getCapacityLiters() const { return capacityLiters_; }
double FuelTank::getCurrentLevelLiters() const { return currentLevelLiters_; }
bool FuelTank::getIsValveOpen() const { return isValveOpen_; }
double FuelTank::getFuelDensityKgPerL() const { return fuelDensityKgPerL_; }

}
