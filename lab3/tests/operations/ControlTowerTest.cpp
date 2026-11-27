#include <gtest/gtest.h>
#include "../../include/operations/ControlTower.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(ControlTowerTest, AuthorizeTakeoffLandingAndEmergency) {
    ControlTower tower("MSQ-TWR", 118.1, 4);
    Flight flight("B2-777", 150, 700);
    Runway rwy("31R", 3600.0);
    Aircraft plane("EW-001", "B737", 41000.0, 78000.0, true);
    WeatherCondition weather(12.0, 6000.0, 18.0, false, false);

    EXPECT_NO_THROW(tower.authorizeTakeoff(flight, rwy, plane, weather));
    EXPECT_EQ(tower.getHandledMovements(), 1);

    tower.authorizeLanding(flight, rwy);
    EXPECT_EQ(tower.getHandledMovements(), 2);

    tower.declareEmergencyOnRunway(rwy);
    EXPECT_TRUE(tower.getEmergencyModeActive());
    EXPECT_THROW(tower.authorizeTakeoff(flight, rwy, plane, weather), RunwayOccupiedException);

    tower.clearEmergency();
    EXPECT_FALSE(tower.getEmergencyModeActive());
    EXPECT_EQ(tower.getTowerCode(), "MSQ-TWR");
    EXPECT_DOUBLE_EQ(tower.getRadioFrequencyMhz(), 118.1);
    EXPECT_EQ(tower.getActiveControllers(), 4);
}
