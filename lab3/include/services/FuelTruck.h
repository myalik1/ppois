#pragma once
#include <string>
#include "../aircraft/FuelTank.h"

namespace airport {

class FuelTruck {
private:
    std::string truckId_;
    double tankCapacityLiters_;
    double remainingFuelLiters_;
    double pumpRateLitersPerMin_;

public:
    FuelTruck(const std::string& truckId,
              double tankCapacityLiters,
              double remainingFuelLiters,
              double pumpRateLitersPerMin);

    double transferFuelToAircraft(FuelTank& aircraftTank, double requestedLiters);
    void refillTruckDepot();
    double estimateRefuelDurationMinutes(double liters) const;

    const std::string& getTruckId() const;
    double getTankCapacityLiters() const;
    double getRemainingFuelLiters() const;
    double getPumpRateLitersPerMin() const;
};

}
