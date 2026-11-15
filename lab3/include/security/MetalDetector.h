#pragma once
#include <string>
#include "../passengers/Passenger.h"

namespace airport {

class MetalDetector {
private:
    std::string detectorId_;
    double thresholdGrams_;
    int alarmTriggersCount_;
    bool isOperational_;

public:
    MetalDetector(const std::string& detectorId,
                  double thresholdGrams,
                  bool isOperational = true);

    bool screenPassenger(const Passenger& passenger, double detectedMetalGrams);
    void resetAlarmCounter();
    void setOperationalState(bool state);

    const std::string& getDetectorId() const;
    double getThresholdGrams() const;
    int getAlarmTriggersCount() const;
    bool getIsOperational() const;
};

}
