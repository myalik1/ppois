#pragma once
#include <string>
#include "../passengers/HandLuggage.h"

namespace airport {

class XRayScanner {
private:
    std::string scannerId_;
    int sensitivityLevel_;
    int scannedBagsCount_;
    bool isCalibrated_;

public:
    XRayScanner(const std::string& scannerId,
                int sensitivityLevel,
                bool isCalibrated = true);

    bool scanHandLuggage(const HandLuggage& luggage, double maxAllowedWeightKg);
    void calibrateScanner();
    void adjustSensitivity(int newSensitivity);

    const std::string& getScannerId() const;
    int getSensitivityLevel() const;
    int getScannedBagsCount() const;
    bool getIsCalibrated() const;
};

}
