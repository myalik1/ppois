#pragma once
namespace airport {

class FuelTank {
private:
    double capacityLiters_;
    double currentLevelLiters_;
    bool isValveOpen_;
    double fuelDensityKgPerL_;

public:
    FuelTank(double capacityLiters,
             double currentLevelLiters,
             bool isValveOpen = false,
             double fuelDensityKgPerL = 0.8);

    double refuel(double litersToAdd);
    void consumeFuel(double litersToBurn);
    double calculateFuelMassKg() const;
    bool hasSufficientFuel(double requiredLiters) const;

    double getCapacityLiters() const;
    double getCurrentLevelLiters() const;
    bool getIsValveOpen() const;
    double getFuelDensityKgPerL() const;
};

}
