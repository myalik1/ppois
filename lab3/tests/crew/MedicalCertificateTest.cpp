#include <gtest/gtest.h>
#include "../../include/crew/MedicalCertificate.h"

using namespace airport;

TEST(MedicalCertificateTest, ValidateSuspendAndExtend) {
    MedicalCertificate med("MED-01", 1, 2026, true);
    EXPECT_TRUE(med.validateMedicalFitness(2026));
    EXPECT_FALSE(med.validateMedicalFitness(2028));

    med.suspendCertificate();
    EXPECT_FALSE(med.getIsFitForDuty());
    EXPECT_FALSE(med.validateMedicalFitness(2026));

    med.voidextendValidity(2);
    EXPECT_EQ(med.getExpiryYear(), 2028);
    EXPECT_TRUE(med.getIsFitForDuty());
    EXPECT_EQ(med.getCertificateId(), "MED-01");
    EXPECT_EQ(med.getMedicalClass(), 1);
}
