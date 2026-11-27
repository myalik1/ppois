#include "../../include/operations/RadarContact.h"

namespace airport {

namespace {
const double kKnotsToKmhFactor = 1.852;
const double kMinutesPerHour = 60.0;
}

RadarContact::RadarContact(const std::string& transponderSquawk,
                           const Flight& flight,
                           double altitudeFeet,
                           double groundSpeedKnots,
                           double distanceToAirportKm)
    : transponderSquawk_(transponderSquawk),
      trackedFlightNumber_(flight.getFlightNumber()),
      altitudeFeet_(altitudeFeet),
      groundSpeedKnots_(groundSpeedKnots),
      distanceToAirportKm_(distanceToAirportKm) {}

bool RadarContact::isEmergencySquawk() const {
    return transponderSquawk_ == "7700" || transponderSquawk_ == "7600" ||
           transponderSquawk_ == "7500";
}

void RadarContact::updatePosition(double newAltitudeFeet, double newDistanceKm) {
    if (newAltitudeFeet >= 0.0 && newDistanceKm >= 0.0) {
        altitudeFeet_ = newAltitudeFeet;
        distanceToAirportKm_ = newDistanceKm;
    }
}

double RadarContact::estimateMinutesToTouchdown() const {
    if (groundSpeedKnots_ <= 0.0 || distanceToAirportKm_ <= 0.0) {
        return 0.0;
    }
    double speedKmh = groundSpeedKnots_ * kKnotsToKmhFactor;
    return (distanceToAirportKm_ / speedKmh) * kMinutesPerHour;
}

const std::string& RadarContact::getTransponderSquawk() const { return transponderSquawk_; }
const std::string& RadarContact::getTrackedFlightNumber() const { return trackedFlightNumber_; }
double RadarContact::getAltitudeFeet() const { return altitudeFeet_; }
double RadarContact::getGroundSpeedKnots() const { return groundSpeedKnots_; }
double RadarContact::getDistanceToAirportKm() const { return distanceToAirportKm_; }

}
