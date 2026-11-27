#pragma once
#include <string>
#include "../passengers/Passenger.h"
#include "../passengers/HandLuggage.h"
#include "XRayScanner.h"
#include "MetalDetector.h"

namespace airport {

class SecurityCheckpoint {
private:
    std::string checkpointId_;
    std::string terminalZone_;
    int clearedPassengersCount_;
    bool isOpen_;
    bool isLockdownActive_;

public:
    SecurityCheckpoint(const std::string& checkpointId,
                       const std::string& terminalZone,
                       bool isOpen = true);

    bool processPassengerScreening(const Passenger& passenger,
                                   const HandLuggage& luggage,
                                   XRayScanner& scanner,
                                   MetalDetector& detector,
                                   double metalGrams);
    void triggerLockdown();
    void liftLockdown();
    void closeCheckpoint();

    const std::string& getCheckpointId() const;
    const std::string& getTerminalZone() const;
    int getClearedPassengersCount() const;
    bool getIsOpen() const;
    bool getIsLockdownActive() const;
};

}
