#include <gtest/gtest.h>
#include "../../include/crew/FlightAttendant.h"

using namespace airport;

TEST(FlightAttendantTest, ReadinessDrillAndPromotion) {
    FlightAttendant attendant("FA-01", "Elena Volkova", 4, false, false);
    MedicalCertificate med("MED-2", 2, 2027, true);

    EXPECT_FALSE(attendant.isReadyForFlight(med, 2026));
    attendant.completeSafetyDrill();
    EXPECT_TRUE(attendant.isReadyForFlight(med, 2026));

    attendant.promoteToPurser();
    EXPECT_TRUE(attendant.getIsSeniorPurser());
    EXPECT_EQ(attendant.getEmployeeId(), "FA-01");
    EXPECT_EQ(attendant.getFullName(), "Elena Volkova");
    EXPECT_EQ(attendant.getExperienceYears(), 4);
    EXPECT_TRUE(attendant.getEmergencyTrainingPassed());
}
