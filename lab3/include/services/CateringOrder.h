#pragma once
#include <string>
#include "../operations/Flight.h"

namespace airport {

class CateringOrder {
private:
    std::string orderId_;
    std::string flightNumber_;
    int standardMealsCount_;
    int businessMealsCount_;
    bool isDelivered_;

public:
    CateringOrder(const std::string& orderId,
                  const Flight& flight,
                  int standardMealsCount,
                  int businessMealsCount);

    double calculateTotalCateringCost(double standardPriceUsd, double businessPriceUsd) const;
    bool deliverToFlight(const Flight& flight);
    void addExtraMeals(int extraStandard, int extraBusiness);

    const std::string& getOrderId() const;
    const std::string& getFlightNumber() const;
    int getStandardMealsCount() const;
    int getBusinessMealsCount() const;
    bool getIsDelivered() const;
};

}
