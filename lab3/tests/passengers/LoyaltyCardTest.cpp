#include <gtest/gtest.h>
#include "../../include/passengers/LoyaltyCard.h"

using namespace airport;

TEST(LoyaltyCardTest, AccrueRedeemAndDiscounts) {
    LoyaltyCard card("LC-100", 15000, "BRONZE", true);
    EXPECT_DOUBLE_EQ(card.calculateDiscountRate(), 0.02);

    card.accrueMiles(10000);
    EXPECT_EQ(card.getMilesBalance(), 25000);
    EXPECT_EQ(card.getTierLevel(), "SILVER");
    EXPECT_DOUBLE_EQ(card.calculateDiscountRate(), 0.08);

    card.accrueMiles(30000);
    EXPECT_EQ(card.getTierLevel(), "GOLD");
    EXPECT_DOUBLE_EQ(card.calculateDiscountRate(), 0.15);

    EXPECT_TRUE(card.redeemMiles(40000));
    EXPECT_EQ(card.getTierLevel(), "BRONZE");
    EXPECT_FALSE(card.redeemMiles(50000));
    EXPECT_EQ(card.getCardNumber(), "LC-100");
    EXPECT_TRUE(card.getIsActive());
}

TEST(LoyaltyCardTest, InactiveCardReturnsZeroDiscount) {
    LoyaltyCard inactive("LC-200", 60000, "GOLD", false);
    EXPECT_DOUBLE_EQ(inactive.calculateDiscountRate(), 0.0);
    EXPECT_FALSE(inactive.redeemMiles(100));
}
