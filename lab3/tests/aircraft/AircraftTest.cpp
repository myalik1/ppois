#include <gtest/gtest.h>
#include "../../include/aircraft/Aircraft.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(AircraftTest, PreFlightWeightAndCapacity) {
    Aircraft plane("EW-455PA", "Boeing 737-800", 41000.0, 79000.0, true);
    Engine engine("ENG-1", "CFM56", 120.0, 1000.0);
    AvionicsSystem avionics("v3.0", true, true, 8);
    LandingGear gear(3, 200.0, 15.0, true);
    FuelTank tank(20000.0, 10000.0);
    CabinLayout layout("B738", 30, 6, 3);

    EXPECT_NO_THROW(plane.performPreFlightCheck(engine, avionics, gear));
    EXPECT_TRUE(plane.getIsAirworthy());
    EXPECT_DOUBLE_EQ(plane.calculateCurrentTakeoffWeight(tank, 15000.0), 64000.0);
    EXPECT_THROW(plane.calculateCurrentTakeoffWeight(tank, 40000.0), BaggageOverweightException);
    EXPECT_TRUE(plane.verifySeatCapacity(layout, 150));

    plane.groundAircraft();
    EXPECT_FALSE(plane.getIsAirworthy());
    EXPECT_EQ(plane.getTailNumber(), "EW-455PA");
    EXPECT_EQ(plane.getModelName(), "Boeing 737-800");
    EXPECT_DOUBLE_EQ(plane.getEmptyWeightKg(), 41000.0);
    EXPECT_DOUBLE_EQ(plane.getMaxTakeoffWeightKg(), 79000.0);
}
