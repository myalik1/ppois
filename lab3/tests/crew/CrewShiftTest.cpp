#include <gtest/gtest.h>
#include "../../include/crew/CrewShift.h"

using namespace airport;

TEST(CrewShiftTest, ValidateCompleteAndAllowance) {
    CrewShift shift("SH-01", 22, 8, true, false);
    Pilot cap("P-1", "Captain", "CAPTAIN", 5000.0, 10.0);
    Pilot fo("P-2", "First Officer", "FIRST_OFFICER", 1500.0, 10.0);
    FlightAttendant purser("FA-1", "Purser", 5, true, true);

    EXPECT_TRUE(shift.validateDutyTimeLimit());
    shift.completeShift(cap, fo);
    EXPECT_TRUE(shift.getIsCompleted());
    EXPECT_DOUBLE_EQ(cap.getTotalFlightHours(), 5008.0);
    EXPECT_DOUBLE_EQ(shift.calculateShiftAllowanceUsd(purser, 20.0), 240.0);
    EXPECT_EQ(shift.getShiftId(), "SH-01");
    EXPECT_EQ(shift.getStartHour(), 22);
    EXPECT_EQ(shift.getDurationHours(), 8);
    EXPECT_TRUE(shift.getIsNightShift());
}
