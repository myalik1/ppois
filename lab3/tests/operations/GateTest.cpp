#include <gtest/gtest.h>
#include "../../include/operations/Gate.h"

using namespace airport;

TEST(GateTest, DockUndockAndBoardingStatus) {
    Gate gate("A10", "Terminal-1", true, false);
    Aircraft plane("EW-777", "B737", 40000.0, 75000.0, true);

    EXPECT_TRUE(gate.dockAircraft(plane));
    EXPECT_FALSE(gate.dockAircraft(plane));
    EXPECT_TRUE(gate.isAvailableForBoarding());
    EXPECT_EQ(gate.getDockedTailNumber(), "EW-777");

    gate.undockAircraft();
    EXPECT_FALSE(gate.getIsOccupied());
    EXPECT_EQ(gate.getGateCode(), "A10");
    EXPECT_EQ(gate.getTerminalName(), "Terminal-1");
    EXPECT_TRUE(gate.getHasJetBridge());
}
