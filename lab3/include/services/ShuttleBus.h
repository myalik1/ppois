#pragma once
#include <string>
#include "../operations/Gate.h"

namespace airport {

class ShuttleBus {
private:
    std::string busId_;
    int maxCapacity_;
    int currentPassengers_;
    std::string assignedGateCode_;
    double batteryChargePercent_;

public:
    ShuttleBus(const std::string& busId,
               int maxCapacity,
               double batteryChargePercent = 100.0);

    bool dispatchToGate(const Gate& gate);
    void boardPassengersOnBus(int count);
    void disembarkAllPassengers();
    void rechargeBattery();

    const std::string& getBusId() const;
    int getMaxCapacity() const;
    int getCurrentPassengers() const;
    const std::string& getAssignedGateCode() const;
    double getBatteryChargePercent() const;
};

}
