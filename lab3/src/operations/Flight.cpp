#include "../../include/operations/Flight.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

Flight::Flight(const std::string& flightNumber,
               int maxPassengers,
               int departureTimeMinutes)
    : flightNumber_(flightNumber),
      status_("SCHEDULED"),
      boardedPassengers_(0),
      maxPassengers_(maxPassengers),
      departureTimeMinutes_(departureTimeMinutes),
      isClearedForTakeoff_(false) {}

void Flight::prepareFlight(const Aircraft& aircraft,
                           const FlightRoute& route,
                           const CrewRoster& roster,
                           Gate& gate) {
    if (!aircraft.getIsAirworthy() || !route.validateRouteParameters() ||
        !roster.getIsRosterComplete()) {
        throw AircraftMaintenanceException("Flight preparation failed: aircraft, route or crew invalid");
    }
    gate.dockAircraft(aircraft);
    status_ = "BOARDING";
}

void Flight::boardPassenger(BoardingPass& pass, const Ticket& ticket) {
    if (boardedPassengers_ >= maxPassengers_) {
        throw FlightOverbookedException("Flight has reached maximum passenger capacity");
    }
    pass.markBoarded(ticket);
    ++boardedPassengers_;
}

void Flight::delayFlight(int delayMinutes) {
    if (delayMinutes > 0) {
        departureTimeMinutes_ += delayMinutes;
        status_ = "DELAYED";
    }
}

void Flight::executeTakeoff(Runway& runway,
                            const Aircraft& aircraft,
                            const WeatherCondition& weather) {
    runway.occupyRunway(aircraft, weather);
    isClearedForTakeoff_ = true;
    status_ = "IN_AIR";
    runway.releaseRunway();
}

void Flight::completeLanding(Runway& runway) {
    runway.releaseRunway();
    status_ = "LANDED";
    isClearedForTakeoff_ = false;
}

const std::string& Flight::getFlightNumber() const { return flightNumber_; }
const std::string& Flight::getStatus() const { return status_; }
int Flight::getBoardedPassengers() const { return boardedPassengers_; }
int Flight::getMaxPassengers() const { return maxPassengers_; }
int Flight::getDepartureTimeMinutes() const { return departureTimeMinutes_; }
bool Flight::getIsClearedForTakeoff() const { return isClearedForTakeoff_; }

}
