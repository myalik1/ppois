#include <gtest/gtest.h>
#include "../../include/passengers/Visa.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(VisaTest, ValidVisaAndChecks) {
    Passport passport("MP1234567", "Anna Petrova", "BLR", 2022, 2032);
    Visa visa("V998877", "DEU", 2027, 90, true);

    EXPECT_NO_THROW(visa.isValidForTravel(passport, 2026));
    EXPECT_TRUE(visa.validateStayDuration(30));
    EXPECT_FALSE(visa.validateStayDuration(120));
    EXPECT_TRUE(visa.matchesDestination("DEU"));
    EXPECT_FALSE(visa.matchesDestination("FRA"));
    EXPECT_EQ(visa.getVisaNumber(), "V998877");
    EXPECT_EQ(visa.getCountryCode(), "DEU");
    EXPECT_EQ(visa.getExpiryYear(), 2027);
    EXPECT_EQ(visa.getMaxStayDays(), 90);
    EXPECT_TRUE(visa.getIsMultipleEntry());
}

TEST(VisaTest, ExpiredVisaOrPassportThrows) {
    Passport passport("MP1234567", "Anna Petrova", "BLR", 2022, 2025);
    Visa visa("V998877", "DEU", 2026, 90, false);

    EXPECT_THROW(visa.isValidForTravel(passport, 2026), InvalidPassportException);

    Passport validPass("MP1234567", "Anna Petrova", "BLR", 2022, 2032);
    EXPECT_THROW(visa.isValidForTravel(validPass, 2028), VisaExpiredException);
}
