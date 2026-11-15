#include "../../include/services/ParkingLot.h"

namespace airport {

namespace {
const int kLongTermDiscountHours = 24;
const double kLongTermDiscountFactor = 0.85;
}
ParkingLot::ParkingLot(const std::string& zoneCode,
                       int totalSpaces,
                       int occupiedSpaces,
                       double hourlyRateUsd,
                       bool isCovered)
    : zoneCode_(zoneCode),
      totalSpaces_(totalSpaces),
      occupiedSpaces_(occupiedSpaces),
      hourlyRateUsd_(hourlyRateUsd),
      isCovered_(isCovered) {}

bool ParkingLot::parkVehicle() {
    if (occupiedSpaces_ >= totalSpaces_) {
        return false;
    }
    ++occupiedSpaces_;
    return true;
}

double ParkingLot::releaseVehicleAndCalculateFee(int parkedHours) {
    if (occupiedSpaces_ > 0) {
        --occupiedSpaces_;
    }
    if (parkedHours <= 0) {
        return 0.0;
    }
    double fee = static_cast<double>(parkedHours) * hourlyRateUsd_;
    return parkedHours >= kLongTermDiscountHours ? fee * kLongTermDiscountFactor : fee;
}

int ParkingLot::getAvailableSpaces() const {
    return totalSpaces_ - occupiedSpaces_;
}

double ParkingLot::calculateOccupancyRate() const {
    if (totalSpaces_ <= 0) {
        return 0.0;
    }
    return static_cast<double>(occupiedSpaces_) / static_cast<double>(totalSpaces_);
}

const std::string& ParkingLot::getZoneCode() const { return zoneCode_; }
int ParkingLot::getTotalSpaces() const { return totalSpaces_; }
int ParkingLot::getOccupiedSpaces() const { return occupiedSpaces_; }
double ParkingLot::getHourlyRateUsd() const { return hourlyRateUsd_; }
bool ParkingLot::getIsCovered() const { return isCovered_; }

} // namespace airport
