#include <gtest/gtest.h>
#include "../../include/passengers/LostBaggageRecord.h"

using namespace airport;

TEST(LostBaggageRecordTest, CompensationAndResolution) {
    Passenger pax("PAX-10", "Dmitry Shipko", 20, false);
    BaggageTag tag("BG-55555", "MSQ", true, false);
    LostBaggageRecord record("CLM-01", pax, tag, 3, false);

    record.incrementMissingDays(2);
    EXPECT_EQ(record.getDaysMissing(), 5);
    EXPECT_DOUBLE_EQ(record.calculateCompensation(50.0), 250.0);

    record.markFound(tag);
    EXPECT_TRUE(record.getIsResolved());
    EXPECT_TRUE(tag.getIsScanned());
    EXPECT_DOUBLE_EQ(record.calculateCompensation(50.0), 0.0);
    EXPECT_EQ(record.getClaimId(), "CLM-01");
    EXPECT_EQ(record.getPassengerId(), "PAX-10");
    EXPECT_EQ(record.getTagCode(), "BG-55555");
}
