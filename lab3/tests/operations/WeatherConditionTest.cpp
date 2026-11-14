#include <gtest/gtest.h>
#include "../../include/operations/WeatherCondition.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(WeatherConditionTest, SafetyAndDeicingChecks) {
    WeatherCondition weather(15.0, 5000.0, -3.0, false, true);
    EXPECT_NO_THROW(weather.verifySafeForFlight());
    EXPECT_TRUE(weather.requiresAircraftDeicing());
    EXPECT_DOUBLE_EQ(weather.getWindSpeedKnots(), 15.0);
    EXPECT_DOUBLE_EQ(weather.getVisibilityMeters(), 5000.0);
    EXPECT_DOUBLE_EQ(weather.getTemperatureCelsius(), -3.0);
    EXPECT_FALSE(weather.getHasThunderstorm());
    EXPECT_TRUE(weather.getIsIcingCondition());

    weather.updateWeatherMetrics(55.0, 300.0, true);
    EXPECT_THROW(weather.verifySafeForFlight(), WeatherHazardException);
}
