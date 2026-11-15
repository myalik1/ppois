#include <gtest/gtest.h>
#include "../../include/aircraft/CabinLayout.h"

using namespace airport;

TEST(CabinLayoutTest, CapacityAndValidation) {
    CabinLayout layout("B737-800", 30, 6, 4);
    Seat seat("5A", "ECONOMY", false, false, 0.0);

    EXPECT_EQ(layout.calculateTotalCapacity(), 180);
    EXPECT_EQ(layout.calculateEconomyCapacity(), 156);
    EXPECT_TRUE(layout.isSeatValidForLayout(seat));
    EXPECT_EQ(layout.getLayoutCode(), "B737-800");
    EXPECT_EQ(layout.getTotalRows(), 30);
    EXPECT_EQ(layout.getSeatsPerRow(), 6);
    EXPECT_EQ(layout.getBusinessRows(), 4);
}
