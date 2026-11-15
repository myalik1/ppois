#include <gtest/gtest.h>
#include "../../include/passengers/Passport.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(PassportTest, ValidPassportOperations) {
    Passport passport("MP1234567", "Ivan Ivanov", "BLR", 2020, 2030);
    EXPECT_NO_THROW(passport.verifyFormat());
    EXPECT_TRUE(passport.isValidForYear(2026));
    EXPECT_FALSE(passport.isValidForYear(2031));
    EXPECT_EQ(passport.remainingValidityYears(2026), 4);
    EXPECT_EQ(passport.remainingValidityYears(2035), 0);
    EXPECT_EQ(passport.getPassportNumber(), "MP1234567");
    EXPECT_EQ(passport.getHolderFullName(), "Ivan Ivanov");
    EXPECT_EQ(passport.getNationality(), "BLR");
    EXPECT_EQ(passport.getIssueYear(), 2020);
    EXPECT_EQ(passport.getExpiryYear(), 2030);
}

TEST(PassportTest, InvalidFormatThrowsException) {
    Passport shortNum("MP12", "Ivan Ivanov", "BLR", 2020, 2030);
    EXPECT_THROW(shortNum.verifyFormat(), InvalidPassportException);

    Passport badYears("MP1234567", "", "BLR", 2030, 2020);
    EXPECT_THROW(badYears.verifyFormat(), InvalidPassportException);
}
