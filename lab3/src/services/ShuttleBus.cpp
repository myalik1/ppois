#include "../../include/services/ShuttleBus.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kTripBatteryCostPercent = 15.0;
const double kMinDispatchBatteryPercent = 20.0;
}

ShuttleBus::ShuttleBus(const std::string& busId,
                       int maxCapacity,
                       double batteryChargePercent)
    : busId_(busId),
      maxCapacity_(maxCapacity),
      currentPassengers_(0),
      assignedGateCode_(""),
      batteryChargePercent_(batteryChargePercent) {}

bool ShuttleBus::dispatchToGate(const Gate& gate) {
    if (batteryChargePercent_ < kMinDispatchBatteryPercent || gate.getGateCode().empty()) {
        return false;
    }
    assignedGateCode_ = gate.getGateCode();
    batteryChargePercent_ -= kTripBatteryCostPercent;
    return true;
}

void ShuttleBus::boardPassengersOnBus(int count) {
    if (count < 0 || currentPassengers_ + count > maxCapacity_) {
        throw FlightOverbookedException("Shuttle bus capacity exceeded");
    }
    currentPassengers_ += count;
}

void ShuttleBus::disembarkAllPassengers() {
    currentPassengers_ = 0;
}

void ShuttleBus::rechargeBattery() {
    batteryChargePercent_ = 100.0;
}

const std::string& ShuttleBus::getBusId() const { return busId_; }
int ShuttleBus::getMaxCapacity() const { return maxCapacity_; }
int ShuttleBus::getCurrentPassengers() const { return currentPassengers_; }
const std::string& ShuttleBus::getAssignedGateCode() const { return assignedGateCode_; }
double ShuttleBus::getBatteryChargePercent() const { return batteryChargePercent_; }

}
