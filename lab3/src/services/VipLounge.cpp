#include "../../include/services/VipLounge.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

VipLounge::VipLounge(const std::string& loungeName,
                     int maxSeatingCapacity,
                     double walkInFeeUsd,
                     bool isBuffetOpen)
    : loungeName_(loungeName),
      maxSeatingCapacity_(maxSeatingCapacity),
      currentGuestsCount_(0),
      walkInFeeUsd_(walkInFeeUsd),
      isBuffetOpen_(isBuffetOpen) {}

bool VipLounge::admitComplimentaryGuest(const Passenger& passenger,
                                        const LoyaltyCard& card,
                                        const Ticket& ticket) {
    ticket.validateTicket();
    if (currentGuestsCount_ >= maxSeatingCapacity_ || !passenger.getIsCheckedIn()) {
        return false;
    }
    if (card.getIsActive() && card.getTierLevel() == "GOLD") {
        ++currentGuestsCount_;
        return true;
    }
    return false;
}

double VipLounge::admitPaidGuest(const Passenger& passenger, double customerFundsUsd) {
    if (currentGuestsCount_ >= maxSeatingCapacity_ || !passenger.getIsCheckedIn()) {
        throw FlightOverbookedException("VIP Lounge is full or guest not checked in");
    }
    if (customerFundsUsd < walkInFeeUsd_) {
        throw InsufficientFundsException("Insufficient funds for VIP Lounge entry");
    }
    ++currentGuestsCount_;
    return customerFundsUsd - walkInFeeUsd_;
}

void VipLounge::checkoutGuest() {
    if (currentGuestsCount_ > 0) {
        --currentGuestsCount_;
    }
}

const std::string& VipLounge::getLoungeName() const { return loungeName_; }
int VipLounge::getMaxSeatingCapacity() const { return maxSeatingCapacity_; }
int VipLounge::getCurrentGuestsCount() const { return currentGuestsCount_; }
double VipLounge::getWalkInFeeUsd() const { return walkInFeeUsd_; }
bool VipLounge::getIsBuffetOpen() const { return isBuffetOpen_; }

}
