#include "../../include/aircraft/LandingGear.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kMinSafeTirePsi = 150.0;
const double kMaxSafeBrakeWearPercent = 80.0;
}

LandingGear::LandingGear(int strutCount,
                         double tirePressurePsi,
                         double brakeWearPercent,
                         bool isDeployed)
    : strutCount_(strutCount),
      tirePressurePsi_(tirePressurePsi),
      brakeWearPercent_(brakeWearPercent),
      isDeployed_(isDeployed) {}

void LandingGear::deployGear() {
    inspectLandingGear();
    isDeployed_ = true;
}

void LandingGear::retractGear() {
    isDeployed_ = false;
}

void LandingGear::inspectLandingGear() const {
    if (tirePressurePsi_ < kMinSafeTirePsi || brakeWearPercent_ > kMaxSafeBrakeWearPercent) {
        throw AircraftMaintenanceException("Landing gear tire pressure or brake wear unsafe");
    }
}

int LandingGear::getStrutCount() const { return strutCount_; }
double LandingGear::getTirePressurePsi() const { return tirePressurePsi_; }
double LandingGear::getBrakeWearPercent() const { return brakeWearPercent_; }
bool LandingGear::getIsDeployed() const { return isDeployed_; }

}
