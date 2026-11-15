#include "../../include/services/FuelTruck.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

FuelTruck::FuelTruck(const std::string& truckId,
                     double tankCapacityLiters,
                     double remainingFuelLiters,
                     double pumpRateLitersPerMin)
    : truckId_(truckId),
      tankCapacityLiters_(tankCapacityLiters),
      remainingFuelLiters_(remainingFuelLiters),
      pumpRateLitersPerMin_(pumpRateLitersPerMin) {}

double FuelTruck::transferFuelToAircraft(FuelTank& aircraftTank, double requestedLiters) {
    if (requestedLiters <= 0.0 || remainingFuelLiters_ < requestedLiters) {
        throw InsufficientFuelException("Fuel truck has insufficient fuel for request");
    }
    double actualTransferred = aircraftTank.refuel(requestedLiters);
    remainingFuelLiters_ -= actualTransferred;
    return actualTransferred;
}

void FuelTruck::refillTruckDepot() {
    remainingFuelLiters_ = tankCapacityLiters_;
}

double FuelTruck::estimateRefuelDurationMinutes(double liters) const {
    if (pumpRateLitersPerMin_ <= 0.0 || liters <= 0.0) {
        return 0.0;
    }
    return liters / pumpRateLitersPerMin_;
}

const std::string& FuelTruck::getTruckId() const { return truckId_; }
double FuelTruck::getTankCapacityLiters() const { return tankCapacityLiters_; }
double FuelTruck::getRemainingFuelLiters() const { return remainingFuelLiters_; }
double FuelTruck::getPumpRateLitersPerMin() const { return pumpRateLitersPerMin_; }

}
