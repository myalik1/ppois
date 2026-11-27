#include "../../include/operations/Runway.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kMinSafeFriction = 0.30;
const double kHeavyJetWeightThresholdKg = 70000.0;
const double kHeavyJetMinRunwayMeters = 2500.0;
const double kStandardMinRunwayMeters = 1500.0;
}

Runway::Runway(const std::string& runwayDesignator,
               double lengthMeters,
               bool isOccupied,
               bool isLit,
               double frictionCoefficient)
    : runwayDesignator_(runwayDesignator),
      lengthMeters_(lengthMeters),
      isOccupied_(isOccupied),
      isLit_(isLit),
      frictionCoefficient_(frictionCoefficient) {}

void Runway::occupyRunway(const Aircraft& aircraft, const WeatherCondition& weather) {
    if (isOccupied_) {
        throw RunwayOccupiedException("Runway " + runwayDesignator_ + " is already occupied");
    }
    weather.verifySafeForFlight();
    if (!isSuitableForAircraft(aircraft) || frictionCoefficient_ < kMinSafeFriction) {
        throw RunwayOccupiedException("Runway unsuitable or friction too low");
    }
    isOccupied_ = true;
}

void Runway::releaseRunway() {
    isOccupied_ = false;
}

bool Runway::isSuitableForAircraft(const Aircraft& aircraft) const {
    double requiredLength = aircraft.getMaxTakeoffWeightKg() >= kHeavyJetWeightThresholdKg
                                ? kHeavyJetMinRunwayMeters
                                : kStandardMinRunwayMeters;
    return lengthMeters_ >= requiredLength && aircraft.getIsAirworthy();
}

void Runway::updateSurfaceFriction(double newFriction) {
    if (newFriction > 0.0 && newFriction <= 1.0) {
        frictionCoefficient_ = newFriction;
    }
}

const std::string& Runway::getRunwayDesignator() const { return runwayDesignator_; }
double Runway::getLengthMeters() const { return lengthMeters_; }
bool Runway::getIsOccupied() const { return isOccupied_; }
bool Runway::getIsLit() const { return isLit_; }
double Runway::getFrictionCoefficient() const { return frictionCoefficient_; }

}
