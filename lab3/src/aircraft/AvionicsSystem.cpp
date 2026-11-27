#include "../../include/aircraft/AvionicsSystem.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const int kMinRequiredSensors = 4;
}

AvionicsSystem::AvionicsSystem(const std::string& firmwareVersion,
                               bool autopilotOperational,
                               bool gpsLocked,
                               int activeSensorCount)
    : firmwareVersion_(firmwareVersion),
      autopilotOperational_(autopilotOperational),
      gpsLocked_(gpsLocked),
      activeSensorCount_(activeSensorCount) {}

void AvionicsSystem::runDiagnostics() const {
    if (!gpsLocked_ || activeSensorCount_ < kMinRequiredSensors) {
        throw AircraftMaintenanceException("Avionics diagnostics failed: GPS or sensors offline");
    }
}

void AvionicsSystem::updateFirmware(const std::string& newVersion) {
    if (!newVersion.empty()) {
        firmwareVersion_ = newVersion;
    }
}

bool AvionicsSystem::engageAutopilot() {
    runDiagnostics();
    return autopilotOperational_;
}

const std::string& AvionicsSystem::getFirmwareVersion() const { return firmwareVersion_; }
bool AvionicsSystem::getAutopilotOperational() const { return autopilotOperational_; }
bool AvionicsSystem::getGpsLocked() const { return gpsLocked_; }
int AvionicsSystem::getActiveSensorCount() const { return activeSensorCount_; }

}
