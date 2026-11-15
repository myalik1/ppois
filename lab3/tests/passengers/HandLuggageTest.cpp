#include <gtest/gtest.h>
#include "../../include/passengers/HandLuggage.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(HandLuggageTest, ValidLuggageInspection) {
    HandLuggage cabinBag(7.5, true, 80, true);
    EXPECT_TRUE(cabinBag.inspectLuggage(10.0));
    EXPECT_DOUBLE_EQ(cabinBag.getWeightKg(), 7.5);
    EXPECT_TRUE(cabinBag.getContainsLiquids());
    EXPECT_EQ(cabinBag.getLiquidVolumeMl(), 80);
    EXPECT_TRUE(cabinBag.getFitsUnderSeat());
}

TEST(HandLuggageTest, ExcessiveLiquidsThrowSecurityBreach) {
    HandLuggage badBag(6.0, true, 250, false);
    EXPECT_THROW(badBag.inspectLuggage(10.0), SecurityBreachException);
}
