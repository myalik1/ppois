#include <gtest/gtest.h>
#include "../../include/passengers/BaggageTag.h"

using namespace airport;

TEST(BaggageTagTest, TagValidationAndScanning) {
    BaggageTag tag("BG-90012", "MSQ", true, false);
    EXPECT_TRUE(tag.validateTagFormat());
    EXPECT_FALSE(tag.getIsScanned());

    tag.markScanned();
    EXPECT_TRUE(tag.getIsScanned());
    EXPECT_TRUE(tag.matchesDestination("MSQ"));
    EXPECT_FALSE(tag.matchesDestination("FRA"));
    EXPECT_EQ(tag.getTagCode(), "BG-90012");
    EXPECT_EQ(tag.getDestinationIata(), "MSQ");
    EXPECT_TRUE(tag.getIsPriority());

    BaggageTag invalidTag("B1", "M", false);
    EXPECT_FALSE(invalidTag.validateTagFormat());
}
