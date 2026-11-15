#include <gtest/gtest.h>
#include "../../include/services/CateringOrder.h"

using namespace airport;

TEST(CateringOrderTest, CostAddMealsAndDeliver) {
    Flight flight("B2-715", 150, 600);
    CateringOrder order("CAT-01", flight, 100, 20);

    order.addExtraMeals(10, 5);
    EXPECT_EQ(order.getStandardMealsCount(), 110);
    EXPECT_EQ(order.getBusinessMealsCount(), 25);
    EXPECT_DOUBLE_EQ(order.calculateTotalCateringCost(10.0, 30.0), 1850.0);

    EXPECT_TRUE(order.deliverToFlight(flight));
    EXPECT_TRUE(order.getIsDelivered());
    EXPECT_EQ(order.getOrderId(), "CAT-01");
    EXPECT_EQ(order.getFlightNumber(), "B2-715");
}
