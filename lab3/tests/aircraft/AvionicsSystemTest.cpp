#include <gtest/gtest.h>
#include "../../include/aircraft/AvionicsSystem.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(AvionicsSystemTest, DiagnosticsAndAutopilot) {
    AvionicsSystem avionics("v2.1", true, true, 6);
    EXPECT_NO_THROW(avionics.runDiagnostics());
    EXPECT_TRUE(avionics.engageAutopilot());

    avionics.updateFirmware("v2.2");
    EXPECT_EQ(avionics.getFirmwareVersion(), "v2.2");
    EXPECT_TRUE(avionics.getAutopilotOperational());
    EXPECT_TRUE(avionics.getGpsLocked());
    EXPECT_EQ(avionics.getActiveSensorCount(), 6);

    AvionicsSystem faulty("v1.0", true, false, 2);
    EXPECT_THROW(faulty.runDiagnostics(), AircraftMaintenanceException);
}
