#include <gtest/gtest.h>
#include "../../include/ticketing/Booking.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(BookingTest, AddTicketsConfirmPromoAndCancel) {
    Passenger pax("PAX-100", "Kirill Myalik", 20, false);
    Booking booking("PNR777", pax);
    EXPECT_THROW(booking.confirmBooking(), InvalidTicketException);

    Ticket ticket("TKT-1", "B2-101", 200.0, true);
    booking.addTicketToBooking(ticket);
    EXPECT_EQ(booking.getTicketCount(), 1);
    EXPECT_DOUBLE_EQ(booking.applyPromoDiscount(10.0), 180.0);

    EXPECT_NO_THROW(booking.confirmBooking());
    EXPECT_TRUE(booking.getIsConfirmed());
    EXPECT_EQ(booking.getPnrCode(), "PNR777");
    EXPECT_EQ(booking.getCustomerId(), "PAX-100");

    booking.cancelBooking();
    EXPECT_FALSE(booking.getIsConfirmed());
    EXPECT_DOUBLE_EQ(booking.getTotalAmountUsd(), 0.0);
}
