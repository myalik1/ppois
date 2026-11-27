#pragma once
#include <string>

namespace airport {

class ParkingLot {
private:
    std::string zoneCode_;
    int totalSpaces_;
    int occupiedSpaces_;
    double hourlyRateUsd_;
    bool isCovered_;

public:
    ParkingLot(const std::string& zoneCode,
               int totalSpaces,
               int occupiedSpaces,
               double hourlyRateUsd,
               bool isCovered);

    bool parkVehicle();
    double releaseVehicleAndCalculateFee(int parkedHours);
    int getAvailableSpaces() const;
    double calculateOccupancyRate() const;

    const std::string& getZoneCode() const;
    int getTotalSpaces() const;
    int getOccupiedSpaces() const;
    double getHourlyRateUsd() const;
    bool getIsCovered() const;
};

}
