#include <gtest/gtest.h>
#include "../../include/aircraft/LandingGear.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(LandingGearTest, DeployRetractAndInspect) {
    LandingGear gear(3, 195.0, 30.0, true);
    EXPECT_NO_THROW(gear.inspectLandingGear());
    gear.retractGear();
    EXPECT_FALSE(gear.getIsDeployed());
    gear.deployGear();
    EXPECT_TRUE(gear.getIsDeployed());
    EXPECT_EQ(gear.getStrutCount(), 3);
    EXPECT_DOUBLE_EQ(gear.getTirePressurePsi(), 195.0);
    EXPECT_DOUBLE_EQ(gear.getBrakeWearPercent(), 30.0);

    LandingGear wornGear(3, 120.0, 90.0, true);
    EXPECT_THROW(wornGear.inspectLandingGear(), AircraftMaintenanceException);
}
