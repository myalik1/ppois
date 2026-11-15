#include "../../include/cli/AirportCLI.h"
#include "../../include/passengers/Passport.h"
#include "../../include/passengers/Visa.h"
#include "../../include/passengers/LoyaltyCard.h"
#include "../../include/passengers/BaggageTag.h"
#include "../../include/passengers/BaggageItem.h"
#include "../../include/passengers/HandLuggage.h"
#include "../../include/passengers/Passenger.h"
#include "../../include/ticketing/Seat.h"
#include "../../include/ticketing/Ticket.h"
#include "../../include/ticketing/Booking.h"
#include "../../include/ticketing/PaymentTransaction.h"
#include "../../include/ticketing/Invoice.h"
#include "../../include/aircraft/Engine.h"
#include "../../include/aircraft/FuelTank.h"
#include "../../include/aircraft/AvionicsSystem.h"
#include "../../include/aircraft/LandingGear.h"
#include "../../include/aircraft/Aircraft.h"
#include "../../include/crew/PilotLicense.h"
#include "../../include/crew/MedicalCertificate.h"
#include "../../include/crew/Pilot.h"
#include "../../include/crew/FlightAttendant.h"
#include "../../include/crew/CrewRoster.h"
#include "../../include/security/XRayScanner.h"
#include "../../include/security/MetalDetector.h"
#include "../../include/security/SecurityCheckpoint.h"
#include "../../include/operations/WeatherCondition.h"
#include "../../include/operations/Runway.h"
#include "../../include/operations/Gate.h"
#include "../../include/operations/FlightRoute.h"
#include "../../include/operations/Flight.h"
#include "../../include/operations/ControlTower.h"
#include "../../include/services/CateringOrder.h"
#include "../../include/services/AirportFinance.h"

namespace airport {

AirportCLI::AirportCLI() : isRunning_(true), executedOperationsCount_(0) {}

void AirportCLI::printMenu(std::ostream& out) const {
    out << "\nAIRPORT MANAGEMENT SYSTEM CLI\n"
        << "1. Passenger Check-In, Ticketing & Invoice Settlement\n"
        << "2. Aircraft Pre-Flight Inspection & Crew Roster Verification\n"
        << "3. Security Checkpoint Screening (X-Ray & Metal Detector)\n"
        << "4. Flight Dispatch, ATC Takeoff & Airport Finance Report\n"
        << "0. Exit\n"
        << "Select option: ";
}

void AirportCLI::handlePassengerAndTicketWorkflow(std::ostream& out) {
    Passport passport("MP7654321", "Kirill Myalik", "BLR", 2022, 2032);
    Visa visa("V-889900", "DEU", 2028, 90, true);
    Passenger passenger("PAX-01", "Kirill Myalik", 20, false);
    passenger.verifyTravelDocuments(passport, visa, 2026);
    passenger.completeCheckIn(passport, 2026);

    Seat seat("4A", "BUSINESS", false, false, 20.0);
    LoyaltyCard card("LC-100", 55000, "GOLD", true);
    Ticket ticket("TKT-901", "B2-715", 200.0, true);
    ticket.calculateFinalPrice(seat, card);
    ticket.assignSeatToPassenger(seat, passenger);

    Booking booking("PNR-MSQ1", passenger);
    booking.addTicketToBooking(ticket);
    PaymentTransaction payment("TX-500", "CARD", 1000.0);
    payment.processPayment(booking);
    Invoice invoice("INV-500", booking, 10.0);
    invoice.settleInvoice(payment);

    out << "[OK] Checked in " << passenger.getFullName()
        << " | Seat: " << seat.getSeatNumber()
        << " | Grand Total Paid: $" << invoice.calculateGrandTotal() << "\n";
}

void AirportCLI::handleAircraftAndCrewWorkflow(std::ostream& out) {
    Aircraft aircraft("EW-455PA", "Boeing 737-800", 41000.0, 79000.0, true);
    Engine engine("ENG-01", "CFM56", 120.0, 1500.0);
    AvionicsSystem avionics("v3.2", true, true, 6);
    LandingGear gear(3, 195.0, 20.0, true);
    aircraft.performPreFlightCheck(engine, avionics, gear);

    Pilot captain("PIL-1", "Captain Morozov", "CAPTAIN", 6500.0);
    Pilot firstOfficer("PIL-2", "Officer Koval", "FIRST_OFFICER", 2100.0);
    FlightAttendant purser("FA-1", "Elena Volkova", 5, true, true);
    CrewRoster roster("RST-715");
    roster.assignPilotToRoster(captain);
    roster.assignPilotToRoster(firstOfficer);
    roster.assignAttendantToRoster(purser);
    roster.verifyMinimumCrewRequirements(45);

    out << "[OK] Aircraft " << aircraft.getTailNumber()
        << " airworthy | Crew Roster complete: "
        << (roster.getIsRosterComplete() ? "YES" : "NO") << "\n";
}

void AirportCLI::handleSecurityAndCustomsWorkflow(std::ostream& out) {
    Passenger passenger("PAX-01", "Kirill Myalik", 20, false, true);
    HandLuggage cabinBag(6.5, true, 75, true);
    XRayScanner scanner("XRAY-A1", 7, true);
    MetalDetector detector("MD-A1", 50.0, true);
    SecurityCheckpoint checkpoint("CP-INTL", "Terminal-A", true);

    checkpoint.processPassengerScreening(passenger, cabinBag, scanner, detector, 12.0);
    out << "[OK] Security screening passed at " << checkpoint.getCheckpointId()
        << " | Cleared count: " << checkpoint.getClearedPassengersCount() << "\n";
}

void AirportCLI::handleFlightAndServicesWorkflow(std::ostream& out) {
    Aircraft aircraft("EW-455PA", "Boeing 737-800", 41000.0, 79000.0, true);
    FlightRoute route("MSQ", "FRA", 1450.0, 34000, true);
    CrewRoster roster("RST-715", 2, 3, true);
    Gate gate("A4", "Terminal-A", true, false);
    Runway runway("31R", 3600.0, false, true, 0.8);
    WeatherCondition weather(12.0, 7000.0, 16.0, false, false);
    Flight flight("B2-715", 150, 720);
    ControlTower tower("MSQ-TWR", 118.1, 3);

    flight.prepareFlight(aircraft, route, roster, gate);
    tower.authorizeTakeoff(flight, runway, aircraft, weather);

    CateringOrder catering("CAT-715", flight, 100, 20);
    AirportFinance finance("2026-Q2", 25000.0, 4000.0, 10000.0);
    finance.payCateringExpense(catering, 10.0, 25.0);

    out << "[OK] Flight " << flight.getFlightNumber()
        << " status: " << flight.getStatus()
        << " | Airport Net Profit: $" << finance.calculateNetProfitUsd() << "\n";
}

bool AirportCLI::processMenuChoice(int choice, std::ostream& out) {
    if (choice == 0) {
        isRunning_ = false;
        out << "Exiting Airport Management System.\n";
        return false;
    }
    if (choice == 1) {
        handlePassengerAndTicketWorkflow(out);
    } else if (choice == 2) {
        handleAircraftAndCrewWorkflow(out);
    } else if (choice == 3) {
        handleSecurityAndCustomsWorkflow(out);
    } else if (choice == 4) {
        handleFlightAndServicesWorkflow(out);
    } else {
        out << "Invalid menu choice.\n";
        return true;
    }
    ++executedOperationsCount_;
    return true;
}

void AirportCLI::runInteractiveLoop(std::istream& in, std::ostream& out) {
    while (isRunning_) {
        printMenu(out);
        int choice = 0;
        if (!(in >> choice)) {
            isRunning_ = false;
            break;
        }
        processMenuChoice(choice, out);
    }
}

bool AirportCLI::getIsRunning() const { return isRunning_; }
int AirportCLI::getExecutedOperationsCount() const { return executedOperationsCount_; }

}
