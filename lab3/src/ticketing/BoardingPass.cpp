#include "../../include/ticketing/BoardingPass.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

BoardingPass::BoardingPass(const std::string& barcode,
                           const std::string& gateNumber,
                           const Ticket& ticket,
                           const Seat& seat,
                           const Passenger& passenger)
    : barcode_(barcode),
      gateNumber_(gateNumber),
      boardingGroup_("GROUP_3"),
      seatNumber_(seat.getSeatNumber()),
      isBoarded_(false) {
    ticket.validateTicket();
    determineBoardingGroup(seat, passenger);
}

void BoardingPass::determineBoardingGroup(const Seat& seat, const Passenger& passenger) {
    if (passenger.getHasSpecialAssistance() || seat.getCabinClass() == "FIRST") {
        boardingGroup_ = "PRIORITY_1";
    } else if (seat.getCabinClass() == "BUSINESS") {
        boardingGroup_ = "PRIORITY_2";
    } else {
        boardingGroup_ = "GROUP_3";
    }
}

void BoardingPass::markBoarded(const Ticket& ticket) {
    ticket.validateTicket();
    if (barcode_.empty()) {
        throw InvalidTicketException("Empty boarding pass barcode");
    }
    isBoarded_ = true;
}

void BoardingPass::updateGate(const std::string& newGate) {
    if (!newGate.empty()) {
        gateNumber_ = newGate;
    }
}

const std::string& BoardingPass::getBarcode() const { return barcode_; }
const std::string& BoardingPass::getGateNumber() const { return gateNumber_; }
const std::string& BoardingPass::getBoardingGroup() const { return boardingGroup_; }
const std::string& BoardingPass::getSeatNumber() const { return seatNumber_; }
bool BoardingPass::getIsBoarded() const { return isBoarded_; }

}
