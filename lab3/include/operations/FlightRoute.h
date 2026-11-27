#pragma once

#include <string>

namespace airport {

class FlightRoute {
private:
    std::string originIata_;
    std::string destinationIata_;
    double distanceKm_;
    int cruisingAltitudeFeet_;
    bool isInternational_;

public:
    FlightRoute(const std::string& originIata,
                const std::string& destinationIata,
                double distanceKm,
                int cruisingAltitudeFeet,
                bool isInternational);

    double estimateFlightDurationHours(double averageSpeedKmh) const;
    double estimateRequiredFuelLiters(double burnRateLitersPerKm) const;
    bool validateRouteParameters() const;

    const std::string& getOriginIata() const;
    const std::string& getDestinationIata() const;
    double getDistanceKm() const;
    int getCruisingAltitudeFeet() const;
    bool getIsInternational() const;
};

}
