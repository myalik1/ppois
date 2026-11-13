#include <gtest/gtest.h>
#include "../../include/ticketing/Ticket.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(TicketTest, PricingSeatAssignmentAndCancellation) {
    Ticket ticket("TKT-500", "B2-715", 100.0, true);
    Seat seat("14C", "ECONOMY", false, false, 20.0);
    LoyaltyCard card("LC-1", 60000, "GOLD", true);
    Passenger pax("PAX-1", "Ivan Ivanov", 25, false);
    FareRule rule("FLEX", true, 10.0, 23.0, 100);

    ticket.calculateFinalPrice(seat, card);
    EXPECT_DOUBLE_EQ(ticket.getFinalPriceUsd(), 102.0);

    EXPECT_NO_THROW(ticket.assignSeatToPassenger(seat, pax));
    EXPECT_TRUE(seat.getIsOccupied());

    double refund = ticket.cancelTicket(rule, seat);
    EXPECT_DOUBLE_EQ(refund, 92.0);
    EXPECT_FALSE(ticket.getIsActive());
    EXPECT_FALSE(seat.getIsOccupied());
    EXPECT_THROW(ticket.validateTicket(), InvalidTicketException);
    EXPECT_EQ(ticket.getTicketNumber(), "TKT-500");
    EXPECT_EQ(ticket.getFlightNumber(), "B2-715");
    EXPECT_DOUBLE_EQ(ticket.getBaseFareUsd(), 100.0);
}
