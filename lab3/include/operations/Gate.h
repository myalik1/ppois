#pragma once

#include <string>
#include "../aircraft/Aircraft.h"

namespace airport {

class Gate {
private:
    std::string gateCode_;
    std::string terminalName_;
    bool hasJetBridge_;
    bool isOccupied_;
    std::string dockedTailNumber_;

public:
    Gate(const std::string& gateCode,
         const std::string& terminalName,
         bool hasJetBridge,
         bool isOccupied = false);

    bool dockAircraft(const Aircraft& aircraft);
    void undockAircraft();
    bool isAvailableForBoarding() const;

    const std::string& getGateCode() const;
    const std::string& getTerminalName() const;
    bool getHasJetBridge() const;
    bool getIsOccupied() const;
    const std::string& getDockedTailNumber() const;
};

}
