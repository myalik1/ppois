#include "../../include/operations/FlightSchedule.h"

namespace airport {

FlightSchedule::FlightSchedule(const std::string& scheduleDate, bool isPublished)
    : scheduleDate_(scheduleDate),
      flights_(),
      delayedFlightsCount_(0),
      isPublished_(isPublished) {}

void FlightSchedule::addFlightToSchedule(const Flight& flight) {
    flights_.push_back(flight);
}

int FlightSchedule::applyWeatherDelayToAll(const WeatherCondition& weather, int delayMinutes) {
    if (!weather.getHasThunderstorm() || delayMinutes <= 0) {
        return 0;
    }
    int delayedCount = 0;
    for (auto& flight : flights_) {
        const std::string& status = flight.getStatus();
        if (status != "LANDED" && status != "COMPLETED") {
            flight.delayFlight(delayMinutes);
            ++delayedCount;
        }
    }
    int totalDelayed = 0;
    for (const auto& flight : flights_) {
        if (flight.getStatus() == "DELAYED") {
            ++totalDelayed;
        }
    }
    delayedFlightsCount_ = totalDelayed;
    return delayedCount;
}

int FlightSchedule::countActiveFlights() const {
    int active = 0;
    for (const auto& flight : flights_) {
        if (flight.getStatus() != "LANDED") {
            ++active;
        }
    }
    return active;
}

bool FlightSchedule::removeCompletedFlights() {
    std::size_t before = flights_.size();
    std::vector<Flight> remaining;
    for (const auto& flight : flights_) {
        if (flight.getStatus() != "LANDED" && flight.getStatus() != "COMPLETED") {
            remaining.push_back(flight);
        }
    }
    flights_ = remaining;
    return flights_.size() < before;
}

const std::string& FlightSchedule::getScheduleDate() const { return scheduleDate_; }
int FlightSchedule::getDelayedFlightsCount() const { return delayedFlightsCount_; }
bool FlightSchedule::getIsPublished() const { return isPublished_; }
std::size_t FlightSchedule::getTotalFlightsCount() const { return flights_.size(); }

}
