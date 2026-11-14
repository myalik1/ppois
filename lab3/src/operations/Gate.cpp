#include "../../include/operations/Gate.h"

namespace airport {

Gate::Gate(const std::string& gateCode,
           const std::string& terminalName,
           bool hasJetBridge,
           bool isOccupied)
    : gateCode_(gateCode),
      terminalName_(terminalName),
      hasJetBridge_(hasJetBridge),
      isOccupied_(isOccupied),
      dockedTailNumber_("") {}

bool Gate::dockAircraft(const Aircraft& aircraft) {
    if (isOccupied_ || aircraft.getTailNumber().empty()) {
        return false;
    }
    isOccupied_ = true;
    dockedTailNumber_ = aircraft.getTailNumber();
    return true;
}

void Gate::undockAircraft() {
    isOccupied_ = false;
    dockedTailNumber_.clear();
}

bool Gate::isAvailableForBoarding() const {
    return isOccupied_ && !dockedTailNumber_.empty();
}

const std::string& Gate::getGateCode() const { return gateCode_; }
const std::string& Gate::getTerminalName() const { return terminalName_; }
bool Gate::getHasJetBridge() const { return hasJetBridge_; }
bool Gate::getIsOccupied() const { return isOccupied_; }
const std::string& Gate::getDockedTailNumber() const { return dockedTailNumber_; }

}
