#include <gtest/gtest.h>
#include "../../include/security/SecurityCheckpoint.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(SecurityCheckpointTest, ScreeningAndLockdown) {
    SecurityCheckpoint cp("CP-NORTH", "Zone-A", true);
    Passenger pax("PAX-1", "Ivan", 25, false, true);
    HandLuggage bag(6.0, false, 0, true);
    XRayScanner scanner("XR-1", 5, true);
    MetalDetector detector("MD-1", 50.0, true);

    EXPECT_TRUE(cp.processPassengerScreening(pax, bag, scanner, detector, 10.0));
    EXPECT_EQ(cp.getClearedPassengersCount(), 1);

    cp.triggerLockdown();
    EXPECT_TRUE(cp.getIsLockdownActive());
    EXPECT_THROW(cp.processPassengerScreening(pax, bag, scanner, detector, 10.0),
                 SecurityBreachException);

    cp.liftLockdown();
    EXPECT_TRUE(cp.getIsOpen());
    cp.closeCheckpoint();
    EXPECT_FALSE(cp.getIsOpen());
    EXPECT_EQ(cp.getCheckpointId(), "CP-NORTH");
    EXPECT_EQ(cp.getTerminalZone(), "Zone-A");
}
