#include "../../include/aircraft/DeicingUnit.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kMinDeicingTempCelsius = 60.0;
}

DeicingUnit::DeicingUnit(const std::string& unitId,
                         double fluidLevelLiters,
                         double fluidTemperatureCelsius,
                         bool isOperational)
    : unitId_(unitId),
      fluidLevelLiters_(fluidLevelLiters),
      fluidTemperatureCelsius_(fluidTemperatureCelsius),
      isOperational_(isOperational) {}

void DeicingUnit::refillFluid(double liters) {
    if (liters > 0.0) {
        fluidLevelLiters_ += liters;
    }
}

void DeicingUnit::heatFluid(double targetCelsius) {
    if (targetCelsius > fluidTemperatureCelsius_) {
        fluidTemperatureCelsius_ = targetCelsius;
    }
}

double DeicingUnit::treatAircraft(const Aircraft& aircraft, double requiredLiters) {
    if (!isOperational_ || aircraft.getTailNumber().empty()) {
        throw AircraftMaintenanceException("Deicing unit is offline or target invalid");
    }
    if (fluidTemperatureCelsius_ < kMinDeicingTempCelsius || fluidLevelLiters_ < requiredLiters) {
        throw AircraftMaintenanceException("Deicing fluid too cold or insufficient");
    }
    fluidLevelLiters_ -= requiredLiters;
    return fluidLevelLiters_;
}

const std::string& DeicingUnit::getUnitId() const { return unitId_; }
double DeicingUnit::getFluidLevelLiters() const { return fluidLevelLiters_; }
double DeicingUnit::getFluidTemperatureCelsius() const { return fluidTemperatureCelsius_; }
bool DeicingUnit::getIsOperational() const { return isOperational_; }

}
