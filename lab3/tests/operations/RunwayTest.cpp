#include <gtest/gtest.h>
#include "../../include/operations/Runway.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(RunwayTest, OccupyReleaseAndSuitability) {
    Runway rwy("31R", 3600.0, false, true, 0.8);
    Aircraft plane("EW-455PA", "B737", 41000.0, 78000.0, true);
    WeatherCondition weather(10.0, 8000.0, 15.0, false, false);

    EXPECT_TRUE(rwy.isSuitableForAircraft(plane));
    EXPECT_NO_THROW(rwy.occupyRunway(plane, weather));
    EXPECT_TRUE(rwy.getIsOccupied());
    EXPECT_THROW(rwy.occupyRunway(plane, weather), RunwayOccupiedException);

    rwy.releaseRunway();
    EXPECT_FALSE(rwy.getIsOccupied());
    rwy.updateSurfaceFriction(0.6);
    EXPECT_DOUBLE_EQ(rwy.getFrictionCoefficient(), 0.6);
    EXPECT_EQ(rwy.getRunwayDesignator(), "31R");
    EXPECT_DOUBLE_EQ(rwy.getLengthMeters(), 3600.0);
    EXPECT_TRUE(rwy.getIsLit());
}
