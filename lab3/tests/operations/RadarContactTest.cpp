#include <gtest/gtest.h>
#include "../../include/operations/RadarContact.h"

using namespace airport;

TEST(RadarContactTest, SquawkPositionAndEta) {
    Flight flight("B2-900", 120, 800);
    RadarContact contact("7700", flight, 12000.0, 250.0, 92.6);

    EXPECT_TRUE(contact.isEmergencySquawk());
    EXPECT_NEAR(contact.estimateMinutesToTouchdown(), 12.0, 0.01);

    contact.updatePosition(4000.0, 20.0);
    EXPECT_DOUBLE_EQ(contact.getAltitudeFeet(), 4000.0);
    EXPECT_DOUBLE_EQ(contact.getDistanceToAirportKm(), 20.0);
    EXPECT_EQ(contact.getTransponderSquawk(), "7700");
    EXPECT_EQ(contact.getTrackedFlightNumber(), "B2-900");
    EXPECT_DOUBLE_EQ(contact.getGroundSpeedKnots(), 250.0);
}
