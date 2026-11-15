#include <gtest/gtest.h>
#include "../../include/ticketing/Seat.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(SeatTest, ReserveReleaseAndPricing) {
    Seat seat("12A", "BUSINESS", true, false, 25.0);
    EXPECT_THROW(seat.reserveSeat(15), InvalidTicketException);
    EXPECT_NO_THROW(seat.reserveSeat(22));
    EXPECT_TRUE(seat.getIsOccupied());
    EXPECT_THROW(seat.reserveSeat(25), FlightOverbookedException);

    EXPECT_DOUBLE_EQ(seat.calculateSeatPrice(100.0), 225.0);
    seat.releaseSeat();
    EXPECT_FALSE(seat.getIsOccupied());

    Seat firstSeat("1A", "FIRST", false, false, 0.0);
    EXPECT_DOUBLE_EQ(firstSeat.calculateSeatPrice(100.0), 350.0);
    EXPECT_EQ(seat.getSeatNumber(), "12A");
    EXPECT_EQ(seat.getCabinClass(), "BUSINESS");
    EXPECT_TRUE(seat.getIsEmergencyExit());
    EXPECT_DOUBLE_EQ(seat.getExtraLegroomFee(), 25.0);
}
