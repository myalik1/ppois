#include "../../include/operations/FlightRoute.h"

namespace airport {

namespace {
const double kReserveFuelMultiplier = 1.15;
const int kMinCruiseAltitudeFeet = 10000;
}

FlightRoute::FlightRoute(const std::string& originIata,
                         const std::string& destinationIata,
                         double distanceKm,
                         int cruisingAltitudeFeet,
                         bool isInternational)
    : originIata_(originIata),
      destinationIata_(destinationIata),
      distanceKm_(distanceKm),
      cruisingAltitudeFeet_(cruisingAltitudeFeet),
      isInternational_(isInternational) {}

double FlightRoute::estimateFlightDurationHours(double averageSpeedKmh) const {
    if (averageSpeedKmh <= 0.0 || distanceKm_ <= 0.0) {
        return 0.0;
    }
    return distanceKm_ / averageSpeedKmh;
}

double FlightRoute::estimateRequiredFuelLiters(double burnRateLitersPerKm) const {
    if (burnRateLitersPerKm <= 0.0 || distanceKm_ <= 0.0) {
        return 0.0;
    }
    return distanceKm_ * burnRateLitersPerKm * kReserveFuelMultiplier;
}

bool FlightRoute::validateRouteParameters() const {
    return !originIata_.empty() && !destinationIata_.empty() &&
           originIata_ != destinationIata_ && distanceKm_ > 0.0 &&
           cruisingAltitudeFeet_ >= kMinCruiseAltitudeFeet;
}

const std::string& FlightRoute::getOriginIata() const { return originIata_; }
const std::string& FlightRoute::getDestinationIata() const { return destinationIata_; }
double FlightRoute::getDistanceKm() const { return distanceKm_; }
int FlightRoute::getCruisingAltitudeFeet() const { return cruisingAltitudeFeet_; }
bool FlightRoute::getIsInternational() const { return isInternational_; }

}
