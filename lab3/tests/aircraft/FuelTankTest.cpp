#include <gtest/gtest.h>
#include "../../include/aircraft/FuelTank.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(FuelTankTest, RefuelConsumeAndMass) {
    FuelTank tank(10000.0, 2000.0);
    EXPECT_DOUBLE_EQ(tank.refuel(5000.0), 5000.0);
    EXPECT_DOUBLE_EQ(tank.getCurrentLevelLiters(), 7000.0);
    EXPECT_DOUBLE_EQ(tank.calculateFuelMassKg(), 5600.0);
    EXPECT_TRUE(tank.hasSufficientFuel(6000.0));

    EXPECT_NO_THROW(tank.consumeFuel(3000.0));
    EXPECT_THROW(tank.consumeFuel(9000.0), InsufficientFuelException);
    EXPECT_DOUBLE_EQ(tank.getCapacityLiters(), 10000.0);
    EXPECT_FALSE(tank.getIsValveOpen());
    EXPECT_DOUBLE_EQ(tank.getFuelDensityKgPerL(), 0.8);
}
