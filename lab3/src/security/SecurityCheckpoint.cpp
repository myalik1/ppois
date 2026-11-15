#include "../../include/security/SecurityCheckpoint.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kStandardMaxCabinKg = 10.0;
}

SecurityCheckpoint::SecurityCheckpoint(const std::string& checkpointId,
                                       const std::string& terminalZone,
                                       bool isOpen)
    : checkpointId_(checkpointId),
      terminalZone_(terminalZone),
      clearedPassengersCount_(0),
      isOpen_(isOpen),
      isLockdownActive_(false) {}

bool SecurityCheckpoint::processPassengerScreening(const Passenger& passenger,
                                                   const HandLuggage& luggage,
                                                   XRayScanner& scanner,
                                                   MetalDetector& detector,
                                                   double metalGrams) {
    if (!isOpen_ || isLockdownActive_) {
        throw SecurityBreachException("Security checkpoint is closed or under lockdown");
    }
    bool bagOk = scanner.scanHandLuggage(luggage, kStandardMaxCabinKg);
    bool bodyOk = detector.screenPassenger(passenger, metalGrams);
    if (bagOk && bodyOk) {
        ++clearedPassengersCount_;
        return true;
    }
    return false;
}

void SecurityCheckpoint::triggerLockdown() {
    isLockdownActive_ = true;
    isOpen_ = false;
}

void SecurityCheckpoint::liftLockdown() {
    isLockdownActive_ = false;
    isOpen_ = true;
}

void SecurityCheckpoint::closeCheckpoint() {
    isOpen_ = false;
}

const std::string& SecurityCheckpoint::getCheckpointId() const { return checkpointId_; }
const std::string& SecurityCheckpoint::getTerminalZone() const { return terminalZone_; }
int SecurityCheckpoint::getClearedPassengersCount() const { return clearedPassengersCount_; }
bool SecurityCheckpoint::getIsOpen() const { return isOpen_; }
bool SecurityCheckpoint::getIsLockdownActive() const { return isLockdownActive_; }

}
