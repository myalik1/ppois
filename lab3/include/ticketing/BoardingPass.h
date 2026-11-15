#pragma once
#include <string>
#include "../passengers/Passenger.h"
#include "Seat.h"
#include "Ticket.h"

namespace airport {

class BoardingPass {
private:
    std::string barcode_;
    std::string gateNumber_;
    std::string boardingGroup_;
    std::string seatNumber_;
    bool isBoarded_;

public:
    BoardingPass(const std::string& barcode,
                 const std::string& gateNumber,
                 const Ticket& ticket,
                 const Seat& seat,
                 const Passenger& passenger);

    void determineBoardingGroup(const Seat& seat, const Passenger& passenger);
    void markBoarded(const Ticket& ticket);
    void updateGate(const std::string& newGate);

    const std::string& getBarcode() const;
    const std::string& getGateNumber() const;
    const std::string& getBoardingGroup() const;
    const std::string& getSeatNumber() const;
    bool getIsBoarded() const;
};

}
