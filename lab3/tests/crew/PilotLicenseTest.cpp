#include <gtest/gtest.h>
#include "../../include/crew/PilotLicense.h"

using namespace airport;

TEST(PilotLicenseTest, ValidityModelMatchAndRenewal) {
    PilotLicense lic("ATPL-900", "Boeing 737-800", 2021, 2026, true);
    EXPECT_TRUE(lic.isLicenseValid(2026));
    EXPECT_FALSE(lic.isLicenseValid(2027));
    EXPECT_TRUE(lic.matchesAircraftModel("Boeing 737-800"));
    EXPECT_FALSE(lic.matchesAircraftModel("A320"));

    lic.renewLicense(5);
    EXPECT_EQ(lic.getExpiryYear(), 2031);
    EXPECT_EQ(lic.getLicenseNumber(), "ATPL-900");
    EXPECT_EQ(lic.getAircraftTypeRating(), "Boeing 737-800");
    EXPECT_EQ(lic.getIssueYear(), 2021);
    EXPECT_TRUE(lic.getHasInstrumentRating());
}
