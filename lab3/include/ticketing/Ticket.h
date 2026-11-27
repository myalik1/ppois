#pragma once
#include <string>
#include "../passengers/Passenger.h"
#include "../passengers/LoyaltyCard.h"
#include "Seat.h"
#include "FareRule.h"

namespace airport {

class Ticket {
private:
    std::string ticketNumber_;
    std::string flightNumber_;
    double baseFareUsd_;
    double finalPriceUsd_;
    bool isActive_;

public:
    Ticket(const std::string& ticketNumber,
           const std::string& flightNumber,
           double baseFareUsd,
           bool isActive = true);

    void calculateFinalPrice(const Seat& seat, const LoyaltyCard& loyaltyCard);
    void assignSeatToPassenger(Seat& seat, const Passenger& passenger) const;
    double cancelTicket(const FareRule& rule, Seat& seat);
    void validateTicket() const;

    const std::string& getTicketNumber() const;
    const std::string& getFlightNumber() const;
    double getBaseFareUsd() const;
    double getFinalPriceUsd() const;
    bool getIsActive() const;
};

}
