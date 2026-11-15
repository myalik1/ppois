#include "../../include/aircraft/Aircraft.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

Aircraft::Aircraft(const std::string& tailNumber,
                   const std::string& modelName,
                   double emptyWeightKg,
                   double maxTakeoffWeightKg,
                   bool isAirworthy)
    : tailNumber_(tailNumber),
      modelName_(modelName),
      emptyWeightKg_(emptyWeightKg),
      maxTakeoffWeightKg_(maxTakeoffWeightKg),
      isAirworthy_(isAirworthy) {}

void Aircraft::performPreFlightCheck(const Engine& engine,
                                     const AvionicsSystem& avionics,
                                     const LandingGear& gear) {
    if (engine.needsOverhaul()) {
        isAirworthy_ = false;
        throw AircraftMaintenanceException("Engine overhaul required on aircraft " + tailNumber_);
    }
    avionics.runDiagnostics();
    gear.inspectLandingGear();
    isAirworthy_ = true;
}

double Aircraft::calculateCurrentTakeoffWeight(const FuelTank& fuelTank, double payloadKg) const {
    double totalWeight = emptyWeightKg_ + fuelTank.calculateFuelMassKg() + payloadKg;
    if (totalWeight > maxTakeoffWeightKg_) {
        throw BaggageOverweightException("Aircraft exceeds maximum takeoff weight");
    }
    return totalWeight;
}

bool Aircraft::verifySeatCapacity(const CabinLayout& layout, int requestedPassengers) const {
    return !tailNumber_.empty() && requestedPassengers >= 0 &&
    requestedPassengers >= 0 && requestedPassengers <= layout.calculateTotalCapacity();
}

void Aircraft::groundAircraft() {
    isAirworthy_ = false;
}

const std::string& Aircraft::getTailNumber() const { return tailNumber_; }
const std::string& Aircraft::getModelName() const { return modelName_; }
double Aircraft::getEmptyWeightKg() const { return emptyWeightKg_; }
double Aircraft::getMaxTakeoffWeightKg() const { return maxTakeoffWeightKg_; }
bool Aircraft::getIsAirworthy() const { return isAirworthy_; }

}
