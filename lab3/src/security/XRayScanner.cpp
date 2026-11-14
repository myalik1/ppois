#include "../../include/security/XRayScanner.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const int kMinSensitivity = 1;
const int kMaxSensitivity = 10;
}

XRayScanner::XRayScanner(const std::string& scannerId,
                         int sensitivityLevel,
                         bool isCalibrated)
    : scannerId_(scannerId),
      sensitivityLevel_(sensitivityLevel),
      scannedBagsCount_(0),
      isCalibrated_(isCalibrated) {}

bool XRayScanner::scanHandLuggage(const HandLuggage& luggage, double maxAllowedWeightKg) {
    if (!isCalibrated_) {
        throw SecurityBreachException("X-Ray scanner is not calibrated");
    }
    bool clean = luggage.inspectLuggage(maxAllowedWeightKg);
    ++scannedBagsCount_;
    return clean;
}

void XRayScanner::calibrateScanner() {
    isCalibrated_ = true;
}

void XRayScanner::adjustSensitivity(int newSensitivity) {
    if (newSensitivity >= kMinSensitivity && newSensitivity <= kMaxSensitivity) {
        sensitivityLevel_ = newSensitivity;
    }
}

const std::string& XRayScanner::getScannerId() const { return scannerId_; }
int XRayScanner::getSensitivityLevel() const { return sensitivityLevel_; }
int XRayScanner::getScannedBagsCount() const { return scannedBagsCount_; }
bool XRayScanner::getIsCalibrated() const { return isCalibrated_; }

}
