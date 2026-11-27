#pragma once
#include <string>

namespace airport {

class Seat {
private:
    std::string seatNumber_;
    std::string cabinClass_;
    bool isEmergencyExit_;
    bool isOccupied_;
    double extraLegroomFee_;

public:
    Seat(const std::string& seatNumber,
         const std::string& cabinClass,
         bool isEmergencyExit,
         bool isOccupied,
         double extraLegroomFee);

    void reserveSeat(int passengerAge);
    void releaseSeat();
    double calculateSeatPrice(double basePrice) const;

    const std::string& getSeatNumber() const;
    const std::string& getCabinClass() const;
    bool getIsEmergencyExit() const;
    bool getIsOccupied() const;
    double getExtraLegroomFee() const;
};

}
