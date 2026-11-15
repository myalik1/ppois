#include <gtest/gtest.h>
#include "../../include/aircraft/MaintenanceLog.h"

using namespace airport;

TEST(MaintenanceLogTest, SignOffDefectAndCurrency) {
    Aircraft plane("EW-001", "E195", 21000.0, 50000.0, true);
    MaintenanceLog log("LOG-1", plane, "Routine A-Check", 2026, false);

    log.signOffMaintenance();
    EXPECT_TRUE(log.getIsClearedToFly());
    EXPECT_TRUE(log.isInspectionCurrent(2026));
    EXPECT_FALSE(log.isInspectionCurrent(2029));

    log.reportDefect(plane, "Hydraulic leak");
    EXPECT_FALSE(log.getIsClearedToFly());
    EXPECT_FALSE(plane.getIsAirworthy());
    EXPECT_EQ(log.getRecordId(), "LOG-1");
    EXPECT_EQ(log.getTailNumber(), "EW-001");
    EXPECT_EQ(log.getDescription(), "Hydraulic leak");
    EXPECT_EQ(log.getInspectionYear(), 2026);
}
