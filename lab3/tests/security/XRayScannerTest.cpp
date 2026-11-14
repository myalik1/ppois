#include <gtest/gtest.h>
#include "../../include/security/XRayScanner.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(XRayScannerTest, ScanCalibrateAndSensitivity) {
    XRayScanner scanner("XRAY-1", 5, false);
    HandLuggage bag(7.0, true, 50, true);

    EXPECT_THROW(scanner.scanHandLuggage(bag, 10.0), SecurityBreachException);
    scanner.calibrateScanner();
    EXPECT_TRUE(scanner.getIsCalibrated());
    EXPECT_TRUE(scanner.scanHandLuggage(bag, 10.0));
    EXPECT_EQ(scanner.getScannedBagsCount(), 1);

    scanner.adjustSensitivity(8);
    EXPECT_EQ(scanner.getSensitivityLevel(), 8);
    EXPECT_EQ(scanner.getScannerId(), "XRAY-1");
}
