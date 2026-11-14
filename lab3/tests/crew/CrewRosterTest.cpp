#include <gtest/gtest.h>
#include "../../include/crew/CrewRoster.h"

using namespace airport;

TEST(CrewRosterTest, AssignAndVerifyMinimumCrew) {
    CrewRoster roster("RST-100");
    Pilot p1("P-1", "Cap", "CAPTAIN", 4000.0);
    Pilot p2("P-2", "FO", "FIRST_OFFICER", 1200.0);
    FlightAttendant fa1("FA-1", "A1", 3, true, true);
    FlightAttendant fa2("FA-2", "A2", 2, false, true);
    CrewShift shift("SH-1", 8, 6, false);

    roster.assignPilotToRoster(p1);
    roster.assignPilotToRoster(p2);
    roster.assignAttendantToRoster(fa1);
    roster.assignAttendantToRoster(fa2);

    EXPECT_EQ(roster.getAssignedPilotsCount(), 2);
    EXPECT_EQ(roster.getAssignedAttendantsCount(), 2);
    EXPECT_TRUE(roster.verifyMinimumCrewRequirements(90));
    EXPECT_TRUE(roster.getIsRosterComplete());
    EXPECT_TRUE(roster.validateRosterForShift(shift));
    EXPECT_EQ(roster.getRosterId(), "RST-100");
}
