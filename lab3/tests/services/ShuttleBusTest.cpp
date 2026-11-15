#include <gtest/gtest.h>
#include "../../include/services/ShuttleBus.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(ShuttleBusTest, DispatchBoardAndRecharge) {
    ShuttleBus bus("BUS-01", 50, 80.0);
    Gate gate("B5", "T2", false, true);

    EXPECT_TRUE(bus.dispatchToGate(gate));
    EXPECT_EQ(bus.getAssignedGateCode(), "B5");
    EXPECT_DOUBLE_EQ(bus.getBatteryChargePercent(), 65.0);

    EXPECT_NO_THROW(bus.boardPassengersOnBus(40));
    EXPECT_EQ(bus.getCurrentPassengers(), 40);
    EXPECT_THROW(bus.boardPassengersOnBus(20), FlightOverbookedException);

    bus.disembarkAllPassengers();
    bus.rechargeBattery();
    EXPECT_EQ(bus.getCurrentPassengers(), 0);
    EXPECT_DOUBLE_EQ(bus.getBatteryChargePercent(), 100.0);
    EXPECT_EQ(bus.getBusId(), "BUS-01");
    EXPECT_EQ(bus.getMaxCapacity(), 50);
}
