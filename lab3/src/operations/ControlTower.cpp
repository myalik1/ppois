#include "../../include/operations/ControlTower.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

ControlTower::ControlTower(const std::string& towerCode,
                           double radioFrequencyMhz,
                           int activeControllers)
    : towerCode_(towerCode),
      radioFrequencyMhz_(radioFrequencyMhz),
      activeControllers_(activeControllers),
      handledMovements_(0),
      emergencyModeActive_(false) {}

void ControlTower::authorizeTakeoff(Flight& flight,
                                    Runway& runway,
                                    const Aircraft& aircraft,
                                    const WeatherCondition& weather) {
    if (emergencyModeActive_ || activeControllers_ <= 0) {
        throw RunwayOccupiedException("Control tower in emergency mode or unstaffed");
    }
    flight.executeTakeoff(runway, aircraft, weather);
    ++handledMovements_;
}

void ControlTower::authorizeLanding(Flight& flight, Runway& runway) {
    flight.completeLanding(runway);
    ++handledMovements_;
}

void ControlTower::declareEmergencyOnRunway(Runway& runway) {
    emergencyModeActive_ = true;
    runway.releaseRunway();
}

void ControlTower::clearEmergency() {
    emergencyModeActive_ = false;
}

const std::string& ControlTower::getTowerCode() const { return towerCode_; }
double ControlTower::getRadioFrequencyMhz() const { return radioFrequencyMhz_; }
int ControlTower::getActiveControllers() const { return activeControllers_; }
int ControlTower::getHandledMovements() const { return handledMovements_; }
bool ControlTower::getEmergencyModeActive() const { return emergencyModeActive_; }

}
