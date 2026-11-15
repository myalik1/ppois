#include <gtest/gtest.h>
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(AirportExceptionsTest, BaseAndDerivedErrorCodesAndMessages) {
    AirportException baseEx("General error", 1000);
    EXPECT_EQ(baseEx.getErrorCode(), 1000);
    EXPECT_STREQ(baseEx.what(), "General error");

    InvalidPassportException passEx("Invalid number");
    EXPECT_EQ(passEx.getErrorCode(), 1001);

    VisaExpiredException visaEx("Expired in 2024");
    EXPECT_EQ(visaEx.getErrorCode(), 1002);

    BaggageOverweightException bagEx("Exceeds 32kg");
    EXPECT_EQ(bagEx.getErrorCode(), 1003);

    InvalidTicketException ticketEx("Ticket cancelled");
    EXPECT_EQ(ticketEx.getErrorCode(), 1004);

    FlightOverbookedException overbookEx("No seats left");
    EXPECT_EQ(overbookEx.getErrorCode(), 1005);

    AircraftMaintenanceException maintEx("Engine overhaul needed");
    EXPECT_EQ(maintEx.getErrorCode(), 1006);

    InsufficientFuelException fuelEx("Tank low");
    EXPECT_EQ(fuelEx.getErrorCode(), 1007);

    RunwayOccupiedException runwayEx("Runway 25L busy");
    EXPECT_EQ(runwayEx.getErrorCode(), 1008);

    WeatherHazardException weatherEx("Storm alert");
    EXPECT_EQ(weatherEx.getErrorCode(), 1009);

    SecurityBreachException secEx("Prohibited item");
    EXPECT_EQ(secEx.getErrorCode(), 1010);

    InsufficientFundsException fundsEx("Balance too low");
    EXPECT_EQ(fundsEx.getErrorCode(), 1011);
}
