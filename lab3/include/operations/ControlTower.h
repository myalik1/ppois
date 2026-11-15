#pragma once
#include <string>
#include "Runway.h"
#include "Flight.h"
#include "WeatherCondition.h"

namespace airport {

class ControlTower {
private:
    std::string towerCode_;
    double radioFrequencyMhz_;
    int activeControllers_;
    int handledMovements_;
    bool emergencyModeActive_;

public:
    ControlTower(const std::string& towerCode,
                 double radioFrequencyMhz,
                 int activeControllers);

    void authorizeTakeoff(Flight& flight,
                          Runway& runway,
                          const Aircraft& aircraft,
                          const WeatherCondition& weather);
    void authorizeLanding(Flight& flight, Runway& runway);
    void declareEmergencyOnRunway(Runway& runway);
    void clearEmergency();

    const std::string& getTowerCode() const;
    double getRadioFrequencyMhz() const;
    int getActiveControllers() const;
    int getHandledMovements() const;
    bool getEmergencyModeActive() const;
};

}
