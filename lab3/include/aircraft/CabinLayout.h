#pragma once
#include <string>
#include "../ticketing/Seat.h"

namespace airport {

class CabinLayout {
private:
    std::string layoutCode_;
    int totalRows_;
    int seatsPerRow_;
    int businessRows_;

public:
    CabinLayout(const std::string& layoutCode,
                int totalRows,
                int seatsPerRow,
                int businessRows);

    int calculateTotalCapacity() const;
    int calculateEconomyCapacity() const;
    bool isSeatValidForLayout(const Seat& seat) const;

    const std::string& getLayoutCode() const;
    int getTotalRows() const;
    int getSeatsPerRow() const;
    int getBusinessRows() const;
};

}
