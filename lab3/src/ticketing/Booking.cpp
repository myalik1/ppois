#include "../../include/ticketing/Booking.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const double kMaxPromoPercent = 50.0;
const double kPercentBase = 100.0;
}

Booking::Booking(const std::string& pnrCode,
                 const Passenger& customer,
                 double totalAmountUsd,
                 bool isConfirmed,
                 int ticketCount)
    : pnrCode_(pnrCode),
      customerId_(customer.getPassengerId()),
      totalAmountUsd_(totalAmountUsd),
      isConfirmed_(isConfirmed),
      ticketCount_(ticketCount) {}

void Booking::addTicketToBooking(const Ticket& ticket) {
    ticket.validateTicket();
    totalAmountUsd_ += ticket.getFinalPriceUsd();
    ++ticketCount_;
}

void Booking::confirmBooking() {
    if (ticketCount_ <= 0 || totalAmountUsd_ <= 0.0) {
        throw InvalidTicketException("Cannot confirm empty booking");
    }
    isConfirmed_ = true;
}

void Booking::cancelBooking() {
    isConfirmed_ = false;
    ticketCount_ = 0;
    totalAmountUsd_ = 0.0;
}

double Booking::applyPromoDiscount(double promoPercent) {
    if (promoPercent > 0.0 && promoPercent <= kMaxPromoPercent) {
        totalAmountUsd_ *= (1.0 - promoPercent / kPercentBase);
    }
    return totalAmountUsd_;
}

const std::string& Booking::getPnrCode() const { return pnrCode_; }
const std::string& Booking::getCustomerId() const { return customerId_; }
double Booking::getTotalAmountUsd() const { return totalAmountUsd_; }
bool Booking::getIsConfirmed() const { return isConfirmed_; }
int Booking::getTicketCount() const { return ticketCount_; }

}
