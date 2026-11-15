#pragma once
#include <string>

namespace airport {

class Engine {
private:
    std::string serialNumber_;
    std::string modelName_;
    double thrustKn_;
    double operatingHours_;
    bool isRunning_;

public:
    Engine(const std::string& serialNumber,
           const std::string& modelName,
           double thrustKn,
           double operatingHours,
           bool isRunning = false);

    void startEngine();
    void shutdownEngine();
    void logFlightHours(double hours);
    bool needsOverhaul() const;

    const std::string& getSerialNumber() const;
    const std::string& getModelName() const;
    double getThrustKn() const;
    double getOperatingHours() const;
    bool getIsRunning() const;
};

}
