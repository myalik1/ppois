#include "../../include/services/CateringOrder.h"

namespace airport {

CateringOrder::CateringOrder(const std::string& orderId,
                             const Flight& flight,
                             int standardMealsCount,
                             int businessMealsCount)
    : orderId_(orderId),
      flightNumber_(flight.getFlightNumber()),
      standardMealsCount_(standardMealsCount),
      businessMealsCount_(businessMealsCount),
      isDelivered_(false) {}

double CateringOrder::calculateTotalCateringCost(double standardPriceUsd,
                                                 double businessPriceUsd) const {
    return standardMealsCount_ * standardPriceUsd + businessMealsCount_ * businessPriceUsd;
}

bool CateringOrder::deliverToFlight(const Flight& flight) {
    if (flight.getFlightNumber() != flightNumber_ || flight.getStatus() == "IN_AIR") {
        return false;
    }
    isDelivered_ = true;
    return true;
}

void CateringOrder::addExtraMeals(int extraStandard, int extraBusiness) {
    if (!isDelivered_ && extraStandard >= 0 && extraBusiness >= 0) {
        standardMealsCount_ += extraStandard;
        businessMealsCount_ += extraBusiness;
    }
}

const std::string& CateringOrder::getOrderId() const { return orderId_; }
const std::string& CateringOrder::getFlightNumber() const { return flightNumber_; }
int CateringOrder::getStandardMealsCount() const { return standardMealsCount_; }
int CateringOrder::getBusinessMealsCount() const { return businessMealsCount_; }
bool CateringOrder::getIsDelivered() const { return isDelivered_; }

}
