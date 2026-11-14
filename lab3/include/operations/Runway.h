#pragma once

#include <string>
#include "../aircraft/Aircraft.h"
#include "WeatherCondition.h"

namespace airport {

class Runway {
private:
    std::string runwayDesignator_;
    double lengthMeters_;
    bool isOccupied_;
    bool isLit_;
    double frictionCoefficient_;

public:
    Runway(const std::string& runwayDesignator,
           double lengthMeters,
           bool isOccupied = false,
           bool isLit = true,
           double frictionCoefficient = 0.75);

    void occupyRunway(const Aircraft& aircraft, const WeatherCondition& weather);
    void releaseRunway();
    bool isSuitableForAircraft(const Aircraft& aircraft) const;
    void updateSurfaceFriction(double newFriction);

    const std::string& getRunwayDesignator() const;
    double getLengthMeters() const;
    bool getIsOccupied() const;
    bool getIsLit() const;
    double getFrictionCoefficient() const;
};

}
