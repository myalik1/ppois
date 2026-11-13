#include "../../include/ticketing/Seat.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const int kMinEmergencyExitAge = 18;
const double kBusinessMultiplier = 2.0;
const double kFirstClassMultiplier = 3.5;
}

Seat::Seat(const std::string& seatNumber,
           const std::string& cabinClass,
           bool isEmergencyExit,
           bool isOccupied,
           double extraLegroomFee)
    : seatNumber_(seatNumber),
      cabinClass_(cabinClass),
      isEmergencyExit_(isEmergencyExit),
      isOccupied_(isOccupied),
      extraLegroomFee_(extraLegroomFee) {}

void Seat::reserveSeat(int passengerAge) {
    if (isOccupied_) {
        throw FlightOverbookedException("Seat is already occupied");
    }
    if (isEmergencyExit_ && passengerAge < kMinEmergencyExitAge) {
        throw InvalidTicketException("Passenger is too young for emergency exit row");
    }
    isOccupied_ = true;
}

void Seat::releaseSeat() {
    isOccupied_ = false;
}

double Seat::calculateSeatPrice(double basePrice) const {
    double multiplier = 1.0;
    if (cabinClass_ == "BUSINESS") {
        multiplier = kBusinessMultiplier;
    } else if (cabinClass_ == "FIRST") {
        multiplier = kFirstClassMultiplier;
    }
    return basePrice * multiplier + extraLegroomFee_;
}

const std::string& Seat::getSeatNumber() const { return seatNumber_; }
const std::string& Seat::getCabinClass() const { return cabinClass_; }
bool Seat::getIsEmergencyExit() const { return isEmergencyExit_; }
bool Seat::getIsOccupied() const { return isOccupied_; }
double Seat::getExtraLegroomFee() const { return extraLegroomFee_; }

}
