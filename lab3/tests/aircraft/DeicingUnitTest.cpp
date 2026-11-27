#include <gtest/gtest.h>
#include "../../include/aircraft/DeicingUnit.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(AircraftDeicingUnitTest, HeatRefillAndTreatAircraft) {
    Aircraft plane("EW-250", "B737", 40000.0, 75000.0, true);
    DeicingUnit unit("DEICE-01", 500.0, 40.0, true);

    EXPECT_THROW(unit.treatAircraft(plane, 200.0), AircraftMaintenanceException);
    unit.heatFluid(75.0);
    unit.refillFluid(300.0);
    EXPECT_DOUBLE_EQ(unit.getFluidLevelLiters(), 800.0);
    EXPECT_DOUBLE_EQ(unit.treatAircraft(plane, 250.0), 550.0);
    EXPECT_EQ(unit.getUnitId(), "DEICE-01");
    EXPECT_DOUBLE_EQ(unit.getFluidTemperatureCelsius(), 75.0);
    EXPECT_TRUE(unit.getIsOperational());
}
