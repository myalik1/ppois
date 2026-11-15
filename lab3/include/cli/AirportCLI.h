#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../passengers/Passport.h"
#include "../passengers/Passenger.h"
#include "../ticketing/Ticket.h"
#include "../aircraft/Aircraft.h"
#include "../operations/Flight.h"
#include "../operations/Runway.h"
#include "../operations/WeatherCondition.h"
#include "../services/AirportFinance.h"

namespace airport {

class AirportCLI {
private:
    bool isRunning_;
    int executedOperationsCount_;
    std::vector<Passenger> passengers_;
    std::vector<Passport> passports_;
    std::vector<Ticket> tickets_;
    std::vector<Aircraft> aircrafts_;
    std::vector<Flight> flights_;
    Runway activeRunway_;
    WeatherCondition currentWeather_;
    AirportFinance finance_;

    void seedInitialState();
    void printMenu(std::ostream& out) const;
    void displayAllData(std::ostream& out) const;
    void displayPassengersAndTickets(std::ostream& out) const;
    void displayFleetAndFlights(std::ostream& out) const;
    void displayWeatherAndFinance(std::ostream& out) const;

    void addPassengerInteractive(std::istream& in, std::ostream& out);
    void checkInAndIssueTicketInteractive(std::istream& in, std::ostream& out);
    void recordTicketPayment(const Passenger& passenger, const Ticket& ticket);
    void cancelTicketInteractive(std::istream& in, std::ostream& out);
    void addAircraftInteractive(std::istream& in, std::ostream& out);
    void modifyAircraftStatusInteractive(std::istream& in, std::ostream& out);
    void addFlightInteractive(std::istream& in, std::ostream& out);
    void updateFlightStatusInteractive(std::istream& in, std::ostream& out);
    void applyFlightAction(Flight& flight, int action, std::istream& in, std::ostream& out);
    void updateWeatherInteractive(std::istream& in, std::ostream& out);
    void runSecurityScreeningInteractive(std::istream& in, std::ostream& out);
    void manageFinanceInteractive(std::istream& in, std::ostream& out);
    bool dispatchChoice(int choice, std::istream& in, std::ostream& out);

public:
    AirportCLI();

    bool processMenuChoice(int choice, std::istream& in, std::ostream& out);
    void runInteractiveLoop(std::istream& in, std::ostream& out);

    bool getIsRunning() const;
    int getExecutedOperationsCount() const;
    std::size_t getPassengersCount() const;
    std::size_t getTicketsCount() const;
    std::size_t getAircraftsCount() const;
    std::size_t getFlightsCount() const;
};

}
