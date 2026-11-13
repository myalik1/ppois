#pragma once
#include <string>
#include <vector>
#include "../passengers/Passenger.h"
#include "Ticket.h"

namespace airport {

class Booking {
private:
    std::string pnrCode_;
    std::string customerId_;
    double totalAmountUsd_;
    bool isConfirmed_;
    int ticketCount_;

public:
    Booking(const std::string& pnrCode,
            const Passenger& customer,
            double totalAmountUsd = 0.0,
            bool isConfirmed = false,
            int ticketCount = 0);

    void addTicketToBooking(const Ticket& ticket);
    void confirmBooking();
    void cancelBooking();
    double applyPromoDiscount(double promoPercent);

    const std::string& getPnrCode() const;
    const std::string& getCustomerId() const;
    double getTotalAmountUsd() const;
    bool getIsConfirmed() const;
    int getTicketCount() const;
};

}
