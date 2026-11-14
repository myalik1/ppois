#include <gtest/gtest.h>
#include "../../include/security/BorderControl.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(BorderControlTest, EntryClearanceAndVisaVerification) {
    BorderControl border("BOOTH-3", "DEU", true);
    Passenger pax("PAX-1", "Ivan Ivanov", 25, false);
    Passport pass("MP1234567", "Ivan Ivanov", "BLR", 2021, 2031);
    Visa visa("V-999", "DEU", 2028, 90, true);
    SecurityBadge badge("SEC-1", "Officer", 3, true);

    EXPECT_TRUE(border.isVisaRequiredForNationality(pass));
    EXPECT_TRUE(border.verifyEntryClearance(pax, pass, visa, badge, 2026));
    EXPECT_EQ(border.getProcessedTravelersCount(), 1);

    border.toggleBiometricGate(false);
    EXPECT_FALSE(border.getIsBiometricGateActive());
    EXPECT_EQ(border.getBoothNumber(), "BOOTH-3");
    EXPECT_EQ(border.getCountryCode(), "DEU");
}
