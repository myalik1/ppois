#include <gtest/gtest.h>
#include "../../include/operations/Flight.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(FlightTest, FullFlightLifecycle) {
    Flight flight("B2-715", 100, 600);
    Aircraft plane("EW-455PA", "B737", 41000.0, 78000.0, true);
    FlightRoute route("MSQ", "DXB", 3800.0, 36000, true);
    CrewRoster roster("RST-1", 2, 3, true);
    Gate gate("A1", "T1", true, false);
    Runway rwy("31L", 3500.0, false, true, 0.8);
    WeatherCondition weather(10.0, 5000.0, 20.0, false, false);

    EXPECT_NO_THROW(flight.prepareFlight(plane, route, roster, gate));
    EXPECT_EQ(flight.getStatus(), "BOARDING");

    Ticket ticket("TKT-1", "B2-715", 200.0, true);
    Seat seat("1A", "BUSINESS", false, true, 0.0);
    Passenger pax("PAX-1", "Test", 30, false, true);
    BoardingPass pass("BC-1", "A1", ticket, seat, pax);

    flight.boardPassenger(pass, ticket);
    EXPECT_EQ(flight.getBoardedPassengers(), 1);

    flight.delayFlight(30);
    EXPECT_EQ(flight.getDepartureTimeMinutes(), 630);
    EXPECT_EQ(flight.getStatus(), "DELAYED");

    flight.executeTakeoff(rwy, plane, weather);
    EXPECT_EQ(flight.getStatus(), "IN_AIR");
    EXPECT_TRUE(flight.getIsClearedForTakeoff());

    flight.completeLanding(rwy);
    EXPECT_EQ(flight.getStatus(), "LANDED");
    EXPECT_EQ(flight.getFlightNumber(), "B2-715");
    EXPECT_EQ(flight.getMaxPassengers(), 100);
}
