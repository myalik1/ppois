#include <gtest/gtest.h>
#include "../../include/crew/GroundTechnician.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(GroundTechnicianTest, InspectApproveAndReportIssue) {
    GroundTechnician tech("TECH-01", "AVIONICS_MECHANICAL", 4, 10, true);
    Aircraft plane("EW-100", "B737", 40000.0, 75000.0, true);
    Engine engine("ENG-1", "CFM56", 120.0, 2000.0);
    LandingGear gear(3, 190.0, 20.0, true);
    MaintenanceLog log("LOG-10", plane, "Check", 2026, false);

    EXPECT_TRUE(tech.isCertifiedForHeavyMaintenance());
    EXPECT_NO_THROW(tech.inspectAndApproveAircraft(engine, gear, log));
    EXPECT_TRUE(log.getIsClearedToFly());
    EXPECT_EQ(tech.getCompletedRepairs(), 11);

    tech.reportTechnicalIssue(plane, log, "Flap sensor fault");
    EXPECT_FALSE(plane.getIsAirworthy());
    EXPECT_EQ(tech.getTechnicianId(), "TECH-01");
    EXPECT_EQ(tech.getSpecialization(), "AVIONICS_MECHANICAL");
    EXPECT_EQ(tech.getCertificationLevel(), 4);
    EXPECT_TRUE(tech.getIsOnShift());
}
