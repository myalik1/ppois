#pragma once
#include <string>
#include "Aircraft.h"

namespace airport {

class DeicingUnit {
private:
    std::string unitId_;
    double fluidLevelLiters_;
    double fluidTemperatureCelsius_;
    bool isOperational_;

public:
    DeicingUnit(const std::string& unitId,
                double fluidLevelLiters,
                double fluidTemperatureCelsius,
                bool isOperational = true);

    void refillFluid(double liters);
    void heatFluid(double targetCelsius);
    double treatAircraft(const Aircraft& aircraft, double requiredLiters);

    const std::string& getUnitId() const;
    double getFluidLevelLiters() const;
    double getFluidTemperatureCelsius() const;
    bool getIsOperational() const;
};

}
