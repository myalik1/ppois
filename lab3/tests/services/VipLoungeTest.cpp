#include <gtest/gtest.h>
#include "../../include/services/VipLounge.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(VipLoungeTest, ComplimentaryPaidAndCheckout) {
    VipLounge lounge("SkyClub", 30, 45.0, true);
    Passenger pax("PAX-1", "Ivan", 28, false, true);
    LoyaltyCard goldCard("LC-1", 60000, "GOLD", true);
    Ticket ticket("TKT-1", "B2-715", 250.0, true);

    EXPECT_TRUE(lounge.admitComplimentaryGuest(pax, goldCard, ticket));
    EXPECT_EQ(lounge.getCurrentGuestsCount(), 1);

    EXPECT_DOUBLE_EQ(lounge.admitPaidGuest(pax, 100.0), 55.0);
    EXPECT_THROW(lounge.admitPaidGuest(pax, 20.0), InsufficientFundsException);

    lounge.checkoutGuest();
    EXPECT_EQ(lounge.getCurrentGuestsCount(), 1);
    EXPECT_EQ(lounge.getLoungeName(), "SkyClub");
    EXPECT_EQ(lounge.getMaxSeatingCapacity(), 30);
    EXPECT_DOUBLE_EQ(lounge.getWalkInFeeUsd(), 45.0);
    EXPECT_TRUE(lounge.getIsBuffetOpen());
}
