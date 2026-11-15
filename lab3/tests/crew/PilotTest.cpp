#include <gtest/gtest.h>
#include "../../include/crew/Pilot.h"

using namespace airport;

TEST(PilotTest, QualificationLoggingAndPromotion) {
    Pilot pilot("PIL-01", "Alexey Smirnov", "FIRST_OFFICER", 2995.0, 40.0);
    PilotLicense lic("LIC-1", "Boeing 737-800", 2020, 2028, true);
    MedicalCertificate med("MED-1", 1, 2027, true);
    Aircraft plane("EW-455PA", "Boeing 737-800", 41000.0, 79000.0, true);

    EXPECT_TRUE(pilot.isQualifiedForAircraft(lic, med, plane, 2026));
    EXPECT_FALSE(pilot.canPromoteToCaptain());

    pilot.logCompletedFlight(8.0);
    EXPECT_DOUBLE_EQ(pilot.getTotalFlightHours(), 3003.0);
    EXPECT_DOUBLE_EQ(pilot.getMonthlyDutyHours(), 48.0);
    EXPECT_TRUE(pilot.canPromoteToCaptain());

    pilot.resetMonthlyDutyHours();
    EXPECT_DOUBLE_EQ(pilot.getMonthlyDutyHours(), 0.0);
    EXPECT_EQ(pilot.getEmployeeId(), "PIL-01");
    EXPECT_EQ(pilot.getFullName(), "Alexey Smirnov");
    EXPECT_EQ(pilot.getRank(), "FIRST_OFFICER");
}
