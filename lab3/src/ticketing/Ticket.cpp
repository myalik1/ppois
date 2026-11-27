#include "../../include/ticketing/Ticket.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

Ticket::Ticket(const std::string& ticketNumber,
               const std::string& flightNumber,
               double baseFareUsd,
               bool isActive)
    : ticketNumber_(ticketNumber),
      flightNumber_(flightNumber),
      baseFareUsd_(baseFareUsd),
      finalPriceUsd_(baseFareUsd),
      isActive_(isActive) {}

void Ticket::calculateFinalPrice(const Seat& seat, const LoyaltyCard& loyaltyCard) {
    double seatPrice = seat.calculateSeatPrice(baseFareUsd_);
    double discount = loyaltyCard.calculateDiscountRate();
    finalPriceUsd_ = seatPrice * (1.0 - discount);
}

void Ticket::assignSeatToPassenger(Seat& seat, const Passenger& passenger) const {
    validateTicket();
    seat.reserveSeat(passenger.getAge());
}

double Ticket::cancelTicket(const FareRule& rule, Seat& seat) {
    validateTicket();
    isActive_ = false;
    seat.releaseSeat();
    return rule.calculateRefundAmount(finalPriceUsd_);
}

void Ticket::validateTicket() const {
    if (!isActive_ || ticketNumber_.empty() || baseFareUsd_ <= 0.0) {
        throw InvalidTicketException("Ticket is inactive or malformed");
    }
}

const std::string& Ticket::getTicketNumber() const { return ticketNumber_; }
const std::string& Ticket::getFlightNumber() const { return flightNumber_; }
double Ticket::getBaseFareUsd() const { return baseFareUsd_; }
double Ticket::getFinalPriceUsd() const { return finalPriceUsd_; }
bool Ticket::getIsActive() const { return isActive_; }

}
