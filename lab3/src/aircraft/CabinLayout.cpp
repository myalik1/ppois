#include "../../include/aircraft/CabinLayout.h"

namespace airport {

CabinLayout::CabinLayout(const std::string& layoutCode,
                         int totalRows,
                         int seatsPerRow,
                         int businessRows)
    : layoutCode_(layoutCode),
      totalRows_(totalRows),
      seatsPerRow_(seatsPerRow),
      businessRows_(businessRows) {}

int CabinLayout::calculateTotalCapacity() const {
    return totalRows_ * seatsPerRow_;
}

int CabinLayout::calculateEconomyCapacity() const {
    int economyRows = totalRows_ - businessRows_;
    return economyRows > 0 ? economyRows * seatsPerRow_ : 0;
}

bool CabinLayout::isSeatValidForLayout(const Seat& seat) const {
    return !seat.getSeatNumber().empty() && calculateTotalCapacity() > 0;
}

const std::string& CabinLayout::getLayoutCode() const { return layoutCode_; }
int CabinLayout::getTotalRows() const { return totalRows_; }
int CabinLayout::getSeatsPerRow() const { return seatsPerRow_; }
int CabinLayout::getBusinessRows() const { return businessRows_; }

}
