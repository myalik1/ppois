#include <gtest/gtest.h>
#include "../../include/services/FuelTruck.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(FuelTruckTest, TransferRefillAndDuration) {
    FuelTruck truck("FT-01", 20000.0, 8000.0, 1000.0);
    FuelTank tank(15000.0, 5000.0);

    EXPECT_DOUBLE_EQ(truck.estimateRefuelDurationMinutes(5000.0), 5.0);
    EXPECT_DOUBLE_EQ(truck.transferFuelToAircraft(tank, 5000.0), 5000.0);
    EXPECT_DOUBLE_EQ(truck.getRemainingFuelLiters(), 3000.0);
    EXPECT_THROW(truck.transferFuelToAircraft(tank, 5000.0), InsufficientFuelException);

    truck.refillTruckDepot();
    EXPECT_DOUBLE_EQ(truck.getRemainingFuelLiters(), 20000.0);
    EXPECT_EQ(truck.getTruckId(), "FT-01");
    EXPECT_DOUBLE_EQ(truck.getTankCapacityLiters(), 20000.0);
    EXPECT_DOUBLE_EQ(truck.getPumpRateLitersPerMin(), 1000.0);
}
