#pragma once

#include <string>
#include <vector>
#include "Flight.h"
#include "WeatherCondition.h"

namespace airport {

class FlightSchedule {
private:
    std::string scheduleDate_;
    std::vector<Flight> flights_;
    int delayedFlightsCount_;
    bool isPublished_;

public:
    explicit FlightSchedule(const std::string& scheduleDate, bool isPublished = true);

    void addFlightToSchedule(const Flight& flight);
    int applyWeatherDelayToAll(const WeatherCondition& weather, int delayMinutes);
    int countActiveFlights() const;
    bool removeCompletedFlights();

    const std::string& getScheduleDate() const;
    int getDelayedFlightsCount() const;
    bool getIsPublished() const;
    std::size_t getTotalFlightsCount() const;
};

}
