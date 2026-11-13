#include <gtest/gtest.h>
#include "../../include/aircraft/Engine.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(EngineTest, StartStopAndOverhaulCheck) {
    Engine engine("ENG-01", "CFM56", 120.0, 4900.0);
    EXPECT_FALSE(engine.needsOverhaul());
    EXPECT_NO_THROW(engine.startEngine());
    EXPECT_TRUE(engine.getIsRunning());

    engine.shutdownEngine();
    EXPECT_FALSE(engine.getIsRunning());

    engine.logFlightHours(150.0);
    EXPECT_TRUE(engine.needsOverhaul());
    EXPECT_THROW(engine.startEngine(), AircraftMaintenanceException);
    EXPECT_EQ(engine.getSerialNumber(), "ENG-01");
    EXPECT_EQ(engine.getModelName(), "CFM56");
    EXPECT_DOUBLE_EQ(engine.getThrustKn(), 120.0);
    EXPECT_DOUBLE_EQ(engine.getOperatingHours(), 5050.0);
}
