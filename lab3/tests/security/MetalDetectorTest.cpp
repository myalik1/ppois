#include <gtest/gtest.h>
#include "../../include/security/MetalDetector.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(MetalDetectorTest, ScreenPassengerAndAlarms) {
    MetalDetector detector("MD-01", 50.0, true);
    Passenger pax("PAX-1", "Ivan", 25, false);

    EXPECT_TRUE(detector.screenPassenger(pax, 15.0));
    EXPECT_THROW(detector.screenPassenger(pax, 120.0), SecurityBreachException);
    EXPECT_EQ(detector.getAlarmTriggersCount(), 1);

    detector.resetAlarmCounter();
    EXPECT_EQ(detector.getAlarmTriggersCount(), 0);
    detector.setOperationalState(false);
    EXPECT_FALSE(detector.getIsOperational());
    EXPECT_EQ(detector.getDetectorId(), "MD-01");
    EXPECT_DOUBLE_EQ(detector.getThresholdGrams(), 50.0);
}
