#pragma once

#include <string>
#include "Flight.h"

namespace airport {

class RadarContact {
private:
    std::string transponderSquawk_;
    std::string trackedFlightNumber_;
    double altitudeFeet_;
    double groundSpeedKnots_;
    double distanceToAirportKm_;

public:
    RadarContact(const std::string& transponderSquawk,
                 const Flight& flight,
                 double altitudeFeet,
                 double groundSpeedKnots,
                 double distanceToAirportKm);

    bool isEmergencySquawk() const;
    void updatePosition(double newAltitudeFeet, double newDistanceKm);
    double estimateMinutesToTouchdown() const;

    const std::string& getTransponderSquawk() const;
    const std::string& getTrackedFlightNumber() const;
    double getAltitudeFeet() const;
    double getGroundSpeedKnots() const;
    double getDistanceToAirportKm() const;
};

}
