#include <gtest/gtest.h>
#include "../../include/services/BaggageConveyor.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(BaggageConveyorTest, StartLoadUnloadAndOverload) {
    BaggageConveyor belt("BELT-1", 40.0, false);
    BaggageItem item(25.0, 50.0, 40.0, 20.0, false);

    EXPECT_THROW(belt.loadBaggageOntoBelt(item), AirportException);
    belt.startBelt();
    EXPECT_TRUE(belt.getIsRunning());

    EXPECT_NO_THROW(belt.loadBaggageOntoBelt(item));
    EXPECT_EQ(belt.getBagsOnBelt(), 1);
    EXPECT_DOUBLE_EQ(belt.getCurrentLoadKg(), 25.0);
    EXPECT_THROW(belt.loadBaggageOntoBelt(item), BaggageOverweightException);

    belt.unloadAllBaggage();
    belt.stopBelt();
    EXPECT_EQ(belt.getBagsOnBelt(), 0);
    EXPECT_FALSE(belt.getIsRunning());
    EXPECT_EQ(belt.getBeltId(), "BELT-1");
    EXPECT_DOUBLE_EQ(belt.getMaxLoadKg(), 40.0);
}
