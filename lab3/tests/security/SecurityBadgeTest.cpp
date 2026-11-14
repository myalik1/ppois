#include <gtest/gtest.h>
#include "../../include/security/SecurityBadge.h"

using namespace airport;

TEST(SecurityBadgeTest, AccessUpgradeAndRevoke) {
    SecurityBadge badge("SEC-10", "Officer Petrov", 3, true);
    EXPECT_TRUE(badge.verifyAccessZone(2));
    EXPECT_FALSE(badge.verifyAccessZone(5));

    badge.upgradeClearance(5);
    EXPECT_EQ(badge.getClearanceLevel(), 5);
    EXPECT_TRUE(badge.verifyAccessZone(5));

    badge.revokeBadge();
    EXPECT_FALSE(badge.getIsActive());
    EXPECT_FALSE(badge.verifyAccessZone(1));
    EXPECT_EQ(badge.getBadgeId(), "SEC-10");
    EXPECT_EQ(badge.getOfficerName(), "Officer Petrov");
}
