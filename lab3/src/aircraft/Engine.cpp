#include "../../include/aircraft/Engine.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kMaxSafeOperatingHours = 5000.0;
}

Engine::Engine(const std::string& serialNumber,
               const std::string& modelName,
               double thrustKn,
               double operatingHours,
               bool isRunning)
    : serialNumber_(serialNumber),
      modelName_(modelName),
      thrustKn_(thrustKn),
      operatingHours_(operatingHours),
      isRunning_(isRunning) {}

void Engine::startEngine() {
    if (needsOverhaul() || thrustKn_ <= 0.0) {
        throw AircraftMaintenanceException("Engine requires overhaul before start");
    }
    isRunning_ = true;
}

void Engine::shutdownEngine() {
    isRunning_ = false;
}

void Engine::logFlightHours(double hours) {
    if (hours > 0.0) {
        operatingHours_ += hours;
    }
}

bool Engine::needsOverhaul() const {
    return operatingHours_ >= kMaxSafeOperatingHours;
}

const std::string& Engine::getSerialNumber() const { return serialNumber_; }
const std::string& Engine::getModelName() const { return modelName_; }
double Engine::getThrustKn() const { return thrustKn_; }
double Engine::getOperatingHours() const { return operatingHours_; }
bool Engine::getIsRunning() const { return isRunning_; }

}
