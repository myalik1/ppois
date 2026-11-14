#include <gtest/gtest.h>
#include "../../include/operations/FlightSchedule.h"

using namespace airport;

TEST(FlightScheduleTest, AddDelayAndFilterFlights) {
    FlightSchedule schedule("2026-05-10", true);
    Flight f1("B2-101", 120, 480);
    Flight f2("B2-102", 150, 540);
    Runway rwy("31L", 3500.0);
    f2.completeLanding(rwy);

    schedule.addFlightToSchedule(f1);
    schedule.addFlightToSchedule(f2);
    EXPECT_EQ(schedule.getTotalFlightsCount(), 2u);
    EXPECT_EQ(schedule.countActiveFlights(), 1);

    WeatherCondition storm(45.0, 400.0, 10.0, true, false);
    EXPECT_EQ(schedule.applyWeatherDelayToAll(storm, 45), 2);
    EXPECT_EQ(schedule.getDelayedFlightsCount(), 2);

    EXPECT_TRUE(schedule.removeCompletedFlights());
    EXPECT_EQ(schedule.getScheduleDate(), "2026-05-10");
    EXPECT_TRUE(schedule.getIsPublished());
}
