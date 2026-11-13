#pragma once
#include <string>

namespace airport {

class AvionicsSystem {
private:
    std::string firmwareVersion_;
    bool autopilotOperational_;
    bool gpsLocked_;
    int activeSensorCount_;

public:
    AvionicsSystem(const std::string& firmwareVersion,
                   bool autopilotOperational,
                   bool gpsLocked,
                   int activeSensorCount);

    void runDiagnostics() const;
    void updateFirmware(const std::string& newVersion);
    bool engageAutopilot();

    const std::string& getFirmwareVersion() const;
    bool getAutopilotOperational() const;
    bool getGpsLocked() const;
    int getActiveSensorCount() const;
};

}
