#include <gtest/gtest.h>
#include "../../include/passengers/BaggageItem.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(BaggageItemTest, VolumeFeeAndTagging) {
    BaggageItem item(25.0, 50.0, 40.0, 20.0, true);
    EXPECT_DOUBLE_EQ(item.calculateVolumeCm3(), 40000.0);
    EXPECT_NO_THROW(item.checkWeightLimit(30.0));
    EXPECT_DOUBLE_EQ(item.calculateOverweightFee(20.0, 10.0), 50.0);
    EXPECT_DOUBLE_EQ(item.calculateOverweightFee(30.0, 10.0), 0.0);

    BaggageTag tag("TAG12345", "MSQ", false);
    EXPECT_TRUE(item.attachTag(tag));
    EXPECT_TRUE(tag.getIsScanned());

    EXPECT_DOUBLE_EQ(item.getWeightKg(), 25.0);
    EXPECT_DOUBLE_EQ(item.getLengthCm(), 50.0);
    EXPECT_DOUBLE_EQ(item.getWidthCm(), 40.0);
    EXPECT_DOUBLE_EQ(item.getHeightCm(), 20.0);
    EXPECT_TRUE(item.getIsFragile());
}

TEST(BaggageItemTest, OverweightThrowsException) {
    BaggageItem heavyItem(35.0, 50.0, 40.0, 20.0, false);
    EXPECT_THROW(heavyItem.checkWeightLimit(32.0), BaggageOverweightException);
}
