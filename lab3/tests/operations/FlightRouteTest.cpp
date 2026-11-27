#include <gtest/gtest.h>
#include "../../include/operations/FlightRoute.h"

using namespace airport;

TEST(FlightRouteTest, DurationFuelAndValidation) {
    FlightRoute route("MSQ", "IST", 1600.0, 35000, true);
    EXPECT_TRUE(route.validateRouteParameters());
    EXPECT_DOUBLE_EQ(route.estimateFlightDurationHours(800.0), 2.0);
    EXPECT_DOUBLE_EQ(route.estimateRequiredFuelLiters(3.0), 5520.0);
    EXPECT_EQ(route.getOriginIata(), "MSQ");
    EXPECT_EQ(route.getDestinationIata(), "IST");
    EXPECT_DOUBLE_EQ(route.getDistanceKm(), 1600.0);
    EXPECT_EQ(route.getCruisingAltitudeFeet(), 35000);
    EXPECT_TRUE(route.getIsInternational());
}
