#include <gtest/gtest.h>
#include "../../include/services/ParkingLot.h"

using namespace airport;

TEST(ParkingLotTest, ParkReleaseAndFeeCalculation) {
    ParkingLot lot("P1-SHORT", 100, 49, 4.0, true);
    EXPECT_TRUE(lot.parkVehicle());
    EXPECT_EQ(lot.getOccupiedSpaces(), 50);
    EXPECT_EQ(lot.getAvailableSpaces(), 50);
    EXPECT_DOUBLE_EQ(lot.calculateOccupancyRate(), 0.5);

    EXPECT_DOUBLE_EQ(lot.releaseVehicleAndCalculateFee(5), 20.0);
    EXPECT_DOUBLE_EQ(lot.releaseVehicleAndCalculateFee(25), 85.0);
    EXPECT_EQ(lot.getZoneCode(), "P1-SHORT");
    EXPECT_EQ(lot.getTotalSpaces(), 100);
    EXPECT_DOUBLE_EQ(lot.getHourlyRateUsd(), 4.0);
    EXPECT_TRUE(lot.getIsCovered());
}
