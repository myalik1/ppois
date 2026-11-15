#pragma once
#include <string>
#include "../passengers/Passenger.h"
#include "../passengers/LoyaltyCard.h"
#include "../ticketing/Ticket.h"

namespace airport {

class VipLounge {
private:
    std::string loungeName_;
    int maxSeatingCapacity_;
    int currentGuestsCount_;
    double walkInFeeUsd_;
    bool isBuffetOpen_;

public:
    VipLounge(const std::string& loungeName,
              int maxSeatingCapacity,
              double walkInFeeUsd,
              bool isBuffetOpen = true);

    bool admitComplimentaryGuest(const Passenger& passenger,
                                 const LoyaltyCard& card,
                                 const Ticket& ticket);
    double admitPaidGuest(const Passenger& passenger, double customerFundsUsd);
    void checkoutGuest();

    const std::string& getLoungeName() const;
    int getMaxSeatingCapacity() const;
    int getCurrentGuestsCount() const;
    double getWalkInFeeUsd() const;
    bool getIsBuffetOpen() const;
};

}
