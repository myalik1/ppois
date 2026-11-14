#include "../../include/security/MetalDetector.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

MetalDetector::MetalDetector(const std::string& detectorId,
                             double thresholdGrams,
                             bool isOperational)
    : detectorId_(detectorId),
      thresholdGrams_(thresholdGrams),
      alarmTriggersCount_(0),
      isOperational_(isOperational) {}

bool MetalDetector::screenPassenger(const Passenger& passenger, double detectedMetalGrams) {
    if (!isOperational_ || passenger.getPassengerId().empty()) {
        throw SecurityBreachException("Metal detector offline or invalid passenger");
    }
    if (detectedMetalGrams > thresholdGrams_) {
        ++alarmTriggersCount_;
        throw SecurityBreachException("Metal detector alarm triggered for passenger");
    }
    return true;
}

void MetalDetector::resetAlarmCounter() {
    alarmTriggersCount_ = 0;
}

void MetalDetector::setOperationalState(bool state) {
    isOperational_ = state;
}

const std::string& MetalDetector::getDetectorId() const { return detectorId_; }
double MetalDetector::getThresholdGrams() const { return thresholdGrams_; }
int MetalDetector::getAlarmTriggersCount() const { return alarmTriggersCount_; }
bool MetalDetector::getIsOperational() const { return isOperational_; }

}
