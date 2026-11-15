#include <gtest/gtest.h>
#include "../../include/ticketing/BoardingPass.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(BoardingPassTest, GroupAssignmentAndBoarding) {
    Ticket ticket("TKT-01", "B2-800", 150.0, true);
    Seat seat("2A", "BUSINESS", false, true, 0.0);
    Passenger pax("PAX-1", "Test User", 30, false, true);

    BoardingPass pass("BC-999", "A4", ticket, seat, pax);
    EXPECT_EQ(pass.getBoardingGroup(), "PRIORITY_2");
    EXPECT_EQ(pass.getSeatNumber(), "2A");

    pass.updateGate("B12");
    EXPECT_EQ(pass.getGateNumber(), "B12");
    EXPECT_NO_THROW(pass.markBoarded(ticket));
    EXPECT_TRUE(pass.getIsBoarded());
    EXPECT_EQ(pass.getBarcode(), "BC-999");

    Passenger specialPax("PAX-2", "Special User", 65, true, true);
    BoardingPass prioPass("BC-1000", "B12", ticket, seat, specialPax);
    EXPECT_EQ(prioPass.getBoardingGroup(), "PRIORITY_1");
}
