#include <gtest/gtest.h>
#include "../../include/ticketing/FareRule.h"

using namespace airport;

TEST(FareRuleTest, RefundChangeAndMilesCalculation) {
    FareRule flex("FLEX-Y", true, 30.0, 23.0, 150);
    EXPECT_DOUBLE_EQ(flex.calculateRefundAmount(200.0), 170.0);
    EXPECT_DOUBLE_EQ(flex.calculateChangeCost(50.0), 80.0);
    EXPECT_EQ(flex.computeEarnedMiles(1000), 1500);
    EXPECT_EQ(flex.getFareCode(), "FLEX-Y");
    EXPECT_TRUE(flex.getIsRefundable());
    EXPECT_DOUBLE_EQ(flex.getChangePenaltyUsd(), 30.0);
    EXPECT_DOUBLE_EQ(flex.getFreeBaggageAllowanceKg(), 23.0);
    EXPECT_EQ(flex.getMilesMultiplierPercent(), 150);

    FareRule promo("PROMO", false, 50.0, 10.0, 0);
    EXPECT_DOUBLE_EQ(promo.calculateRefundAmount(200.0), 0.0);
    EXPECT_EQ(promo.computeEarnedMiles(1000), 0);
}
