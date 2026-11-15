#pragma once
#include <string>
#include "../aircraft/Aircraft.h"
#include "FlightRoute.h"
#include "Gate.h"
#include "Runway.h"
#include "../crew/CrewRoster.h"
#include "../ticketing/BoardingPass.h"

namespace airport {

class Flight {
private:
    std::string flightNumber_;
    std::string status_;
    int boardedPassengers_;
    int maxPassengers_;
    int departureTimeMinutes_;
    bool isClearedForTakeoff_;

public:
    Flight(const std::string& flightNumber,
           int maxPassengers,
           int departureTimeMinutes);

    void prepareFlight(const Aircraft& aircraft,
                       const FlightRoute& route,
                       const CrewRoster& roster,
                       Gate& gate);
    void boardPassenger(BoardingPass& pass, const Ticket& ticket);
    void delayFlight(int delayMinutes);
    void executeTakeoff(Runway& runway,
                        const Aircraft& aircraft,
                        const WeatherCondition& weather);
    void completeLanding(Runway& runway);

    const std::string& getFlightNumber() const;
    const std::string& getStatus() const;
    int getBoardedPassengers() const;
    int getMaxPassengers() const;
    int getDepartureTimeMinutes() const;
    bool getIsClearedForTakeoff() const;
};

}
