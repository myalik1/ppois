#include "../../include/cli/AirportCLI.h"
#include "../../include/exceptions/AirportExceptions.h"
#include "../../include/passengers/LoyaltyCard.h"
#include "../../include/passengers/HandLuggage.h"
#include "../../include/ticketing/Seat.h"
#include "../../include/ticketing/FareRule.h"
#include "../../include/ticketing/Booking.h"
#include "../../include/ticketing/PaymentTransaction.h"
#include "../../include/ticketing/Invoice.h"
#include "../../include/aircraft/Engine.h"
#include "../../include/aircraft/AvionicsSystem.h"
#include "../../include/aircraft/LandingGear.h"
#include "../../include/security/XRayScanner.h"
#include "../../include/security/MetalDetector.h"
#include "../../include/security/SecurityCheckpoint.h"
#include "../../include/services/CateringOrder.h"

namespace airport {

namespace {
const int kCurrentYear = 2026;
const double kDefaultRunwayLengthM = 3600.0;
const double kDefaultWindKnots = 10.0;
const double kDefaultVisibilityM = 8000.0;
const double kDefaultTempC = 18.0;
const double kInitialRevenueUsd = 20000.0;
const double kInitialExpensesUsd = 5000.0;
const double kInitialReserveUsd = 10000.0;
const double kDefaultCustomerBalanceUsd = 5000.0;
const double kDefaultTaxPercent = 10.0;
const double kDefaultCancelPenaltyUsd = 25.0;
const double kDefaultBagAllowanceKg = 23.0;
const int kDefaultMilesPercent = 100;
const double kStandardEngineThrustKn = 120.0;
const double kStandardEngineHours = 1200.0;
const int kStandardSensorsCount = 6;
const int kStandardStrutCount = 3;
const double kStandardTirePsi = 195.0;
const double kStandardBrakeWear = 15.0;
const int kDefaultScannerSensitivity = 7;
const double kDefaultMetalThresholdGrams = 50.0;
const double kStandardMealPriceUsd = 12.0;
const double kBusinessMealPriceUsd = 30.0;
}

AirportCLI::AirportCLI()
    : isRunning_(true),
      executedOperationsCount_(0),
      activeRunway_("31R", kDefaultRunwayLengthM, false, true),
      currentWeather_(kDefaultWindKnots, kDefaultVisibilityM, kDefaultTempC, false, false),
      finance_("2026-Q2", kInitialRevenueUsd, kInitialExpensesUsd, kInitialReserveUsd) {
    seedInitialState();
}

void AirportCLI::seedInitialState() {
    Passport defaultPassport("MP1234567", "Ivan Ivanov", "BLR", 2021, 2031);
    Passenger defaultPassenger("PAX-1", "Ivan Ivanov", 25, false, false);
    passengers_.push_back(defaultPassenger);
    passports_.push_back(defaultPassport);

    Aircraft defaultAircraft("EW-455PA", "Boeing-737", 41000.0, 79000.0, true);
    aircrafts_.push_back(defaultAircraft);

    Flight defaultFlight("B2-715", 150, 600);
    flights_.push_back(defaultFlight);
}

void AirportCLI::printMenu(std::ostream& out) {
    out << "\n================ AIRPORT MANAGEMENT SYSTEM ================\n"
        << "1. View All Airport Data (Passengers, Tickets, Fleet, Flights)\n"
        << "2. Register New Passenger & Passport\n"
        << "3. Check-In Passenger & Issue Ticket\n"
        << "4. Cancel Existing Ticket & Process Refund\n"
        << "5. Add New Aircraft to Fleet\n"
        << "6. Modify Aircraft Airworthiness (Inspect / Ground)\n"
        << "7. Create & Schedule New Flight\n"
        << "8. Manage Flight Status (Delay / Takeoff / Land)\n"
        << "9. Update Weather Conditions\n"
        << "10. Run Passenger Security Screening\n"
        << "11. Order Flight Catering & Allocate Reserve Funds\n"
        << "0. Exit\n"
        << "Enter choice: ";
}

void AirportCLI::displayAllData(std::ostream& out) const {
    displayPassengersAndTickets(out);
    displayFleetAndFlights(out);
    displayWeatherAndFinance(out);
}

void AirportCLI::displayPassengersAndTickets(std::ostream& out) const {
    out << "\n--- PASSENGERS (" << passengers_.size() << ") ---\n";
    for (std::size_t i = 0; i < passengers_.size(); ++i) {
        const Passenger& pax = passengers_[i];
        const Passport& pass = passports_[i];
        out << "[" << i << "] ID: " << pax.getPassengerId() << " | Name: " << pax.getFullName()
            << " | Age: " << pax.getAge() << " | Passport: " << pass.getPassportNumber()
            << " | Checked-In: " << (pax.getIsCheckedIn() ? "YES" : "NO") << "\n";
    }
    out << "--- TICKETS (" << tickets_.size() << ") ---\n";
    for (std::size_t i = 0; i < tickets_.size(); ++i) {
        const Ticket& tkt = tickets_[i];
        out << "[" << i << "] No: " << tkt.getTicketNumber() << " | Flight: "
            << tkt.getFlightNumber() << " | Price: $" << tkt.getFinalPriceUsd()
            << " | Active: " << (tkt.getIsActive() ? "YES" : "NO") << "\n";
    }
}

void AirportCLI::displayFleetAndFlights(std::ostream& out) const {
    out << "--- AIRCRAFT FLEET (" << aircrafts_.size() << ") ---\n";
    for (std::size_t i = 0; i < aircrafts_.size(); ++i) {
        const Aircraft& plane = aircrafts_[i];
        out << "[" << i << "] Tail: " << plane.getTailNumber() << " | Model: "
            << plane.getModelName() << " | MaxWeight: " << plane.getMaxTakeoffWeightKg()
            << "kg | Airworthy: " << (plane.getIsAirworthy() ? "YES" : "NO") << "\n";
    }
    out << "--- FLIGHTS (" << flights_.size() << ") ---\n";
    for (std::size_t i = 0; i < flights_.size(); ++i) {
        const Flight& flt = flights_[i];
        out << "[" << i << "] Flight: " << flt.getFlightNumber() << " | Status: "
            << flt.getStatus() << " | DepTime(min): " << flt.getDepartureTimeMinutes()
            << " | Capacity: " << flt.getMaxPassengers() << "\n";
    }
}

void AirportCLI::displayWeatherAndFinance(std::ostream& out) const {
    out << "--- WEATHER & RUNWAY ---\n"
        << "Runway: " << activeRunway_.getRunwayDesignator() << " | Wind: "
        << currentWeather_.getWindSpeedKnots() << " kt | Visibility: "
        << currentWeather_.getVisibilityMeters() << " m | Storm: "
        << (currentWeather_.getHasThunderstorm() ? "YES" : "NO") << "\n"
        << "--- FINANCE (" << finance_.getFiscalPeriod() << ") ---\n"
        << "Revenue: $" << finance_.getTotalRevenueUsd() << " | Expenses: $"
        << finance_.getTotalExpensesUsd() << " | Net Profit: $"
        << finance_.calculateNetProfitUsd() << " | Reserve: $"
        << finance_.getReserveFundUsd() << "\n";
}

void AirportCLI::addPassengerInteractive(std::istream& in, std::ostream& out) {
    std::string id;
    std::string fullName;
    int age = 0;
    std::string passNum;
    std::string nationality;
    int issueYear = 0;
    int expiryYear = 0;
    out << "Enter Passenger ID (e.g. PAX-2): ";
    in >> id;
    out << "Enter Full Name: ";
    std::getline(in >> std::ws, fullName);
    out << "Enter Age: ";
    in >> age;
    out << "Enter Passport Number (6-12 chars), Nationality, IssueYear, ExpiryYear: ";
    in >> passNum >> nationality >> issueYear >> expiryYear;

    Passport passport(passNum, fullName, nationality, issueYear, expiryYear);
    passport.verifyFormat();
    Passenger passenger(id, fullName, age, false, false);
    passengers_.push_back(passenger);
    passports_.push_back(passport);
    out << "[OK] Passenger " << fullName << " registered at index "
        << (passengers_.size() - 1) << ".\n";
}

void AirportCLI::checkInAndIssueTicketInteractive(std::istream& in, std::ostream& out) {
    std::size_t paxIndex = 0;
    std::string ticketNum;
    std::string flightNum;
    double baseFare = 0.0;
    std::string seatNum;
    std::string cabinClass;
    out << "Enter Passenger index (0.." << (passengers_.size() - 1) << "): ";
    in >> paxIndex;
    if (paxIndex >= passengers_.size()) {
        out << "[ERROR] Invalid passenger index.\n";
        return;
    }
    out << "Enter TicketNo, FlightNo, BaseFare($), SeatNo, Class(ECONOMY/BUSINESS/FIRST): ";
    in >> ticketNum >> flightNum >> baseFare >> seatNum >> cabinClass;

    passengers_[paxIndex].completeCheckIn(passports_[paxIndex], kCurrentYear);
    Seat seat(seatNum, cabinClass, false, false, 0.0);
    LoyaltyCard card("LC-STD", 10000, "BRONZE", true);
    Ticket ticket(ticketNum, flightNum, baseFare, true);
    ticket.calculateFinalPrice(seat, card);
    ticket.assignSeatToPassenger(seat, passengers_[paxIndex]);
    recordTicketPayment(passengers_[paxIndex], ticket);
    tickets_.push_back(ticket);
    out << "[OK] Checked in & issued ticket " << ticketNum
        << " | Final Price: $" << ticket.getFinalPriceUsd() << "\n";
}

void AirportCLI::recordTicketPayment(const Passenger& passenger, const Ticket& ticket) {
    Booking booking("PNR-" + ticket.getTicketNumber(), passenger);
    booking.addTicketToBooking(ticket);
    PaymentTransaction tx("TX-" + ticket.getTicketNumber(), "CARD", kDefaultCustomerBalanceUsd);
    tx.processPayment(booking);
    Invoice invoice("INV-" + ticket.getTicketNumber(), booking, kDefaultTaxPercent);
    invoice.settleInvoice(tx);
    finance_.recordInvoiceRevenue(invoice, tx);
}

void AirportCLI::cancelTicketInteractive(std::istream& in, std::ostream& out) {
    if (tickets_.empty()) {
        out << "[ERROR] No tickets available to cancel.\n";
        return;
    }
    std::size_t tktIndex = 0;
    out << "Enter Ticket index (0.." << (tickets_.size() - 1) << "): ";
    in >> tktIndex;
    if (tktIndex >= tickets_.size()) {
        out << "[ERROR] Invalid ticket index.\n";
        return;
    }
    Seat seat("1A", "ECONOMY", false, true, 0.0);
    FareRule rule("FLEX", true, kDefaultCancelPenaltyUsd, kDefaultBagAllowanceKg, kDefaultMilesPercent);
    double refund = tickets_[tktIndex].cancelTicket(rule, seat);
    out << "[OK] Ticket " << tickets_[tktIndex].getTicketNumber()
        << " cancelled. Refund amount: $" << refund << "\n";
}

void AirportCLI::addAircraftInteractive(std::istream& in, std::ostream& out) {
    std::string tailNumber;
    std::string modelName;
    double emptyWeightKg = 0.0;
    double maxTakeoffWeightKg = 0.0;
    out << "Enter TailNumber, Model(no spaces), EmptyWeight(kg), MaxTakeoffWeight(kg): ";
    in >> tailNumber >> modelName >> emptyWeightKg >> maxTakeoffWeightKg;

    Aircraft aircraft(tailNumber, modelName, emptyWeightKg, maxTakeoffWeightKg, true);
    aircrafts_.push_back(aircraft);
    out << "[OK] Aircraft " << tailNumber << " added at index "
        << (aircrafts_.size() - 1) << ".\n";
}

void AirportCLI::modifyAircraftStatusInteractive(std::istream& in, std::ostream& out) {
    std::size_t idx = 0;
    int action = 0;
    out << "Enter Aircraft index (0.." << (aircrafts_.size() - 1)
        << ") and Action (1=PreFlightCheck/Restore, 2=Ground): ";
    in >> idx >> action;
    if (idx >= aircrafts_.size()) {
        out << "[ERROR] Invalid aircraft index.\n";
        return;
    }
    if (action == 2) {
        aircrafts_[idx].groundAircraft();
        out << "[OK] Aircraft " << aircrafts_[idx].getTailNumber() << " grounded.\n";
    } else {
        Engine eng("ENG-1", "CFM56", kStandardEngineThrustKn, kStandardEngineHours);
        AvionicsSystem av("v3.0", true, true, kStandardSensorsCount);
        LandingGear gear(kStandardStrutCount, kStandardTirePsi, kStandardBrakeWear, true);
        aircrafts_[idx].performPreFlightCheck(eng, av, gear);
        out << "[OK] Aircraft " << aircrafts_[idx].getTailNumber() << " is airworthy.\n";
    }
}

void AirportCLI::addFlightInteractive(std::istream& in, std::ostream& out) {
    std::string flightNumber;
    int maxPassengers = 0;
    int departureMinutes = 0;
    out << "Enter FlightNumber, MaxPassengers, DepartureTime(minutes from midnight): ";
    in >> flightNumber >> maxPassengers >> departureMinutes;

    Flight flight(flightNumber, maxPassengers, departureMinutes);
    flights_.push_back(flight);
    out << "[OK] Flight " << flightNumber << " scheduled at index "
        << (flights_.size() - 1) << ".\n";
}

void AirportCLI::updateFlightStatusInteractive(std::istream& in, std::ostream& out) {
    std::size_t fltIdx = 0;
    int action = 0;
    out << "Enter Flight index (0.." << (flights_.size() - 1)
        << ") and Action (1=Delay, 2=Takeoff, 3=Land): ";
    in >> fltIdx >> action;
    if (fltIdx >= flights_.size()) {
        out << "[ERROR] Invalid flight index.\n";
        return;
    }
    applyFlightAction(flights_[fltIdx], action, in, out);
}

void AirportCLI::applyFlightAction(Flight& flight, int action, std::istream& in, std::ostream& out) {
    if (action == 1) {
        int delayMins = 0;
        out << "Enter delay minutes: ";
        in >> delayMins;
        flight.delayFlight(delayMins);
    } else if (action == 2) {
        std::size_t planeIdx = 0;
        out << "Enter Aircraft index for takeoff (0.." << (aircrafts_.size() - 1) << "): ";
        in >> planeIdx;
        if (planeIdx >= aircrafts_.size()) {
            out << "[ERROR] Invalid aircraft index.\n";
            return;
        }
        flight.executeTakeoff(activeRunway_, aircrafts_[planeIdx], currentWeather_);
    } else if (action == 3) {
        flight.completeLanding(activeRunway_);
    }
    out << "[OK] Flight " << flight.getFlightNumber() << " status updated to "
        << flight.getStatus() << " (Dep: " << flight.getDepartureTimeMinutes() << "m).\n";
}

void AirportCLI::updateWeatherInteractive(std::istream& in, std::ostream& out) {
    double windKnots = 0.0;
    double visibilityM = 0.0;
    int stormFlag = 0;
    out << "Enter WindSpeed(knots), Visibility(meters), Thunderstorm(1=Yes, 0=No): ";
    in >> windKnots >> visibilityM >> stormFlag;

    currentWeather_.updateWeatherMetrics(windKnots, visibilityM, stormFlag != 0);
    currentWeather_.verifySafeForFlight();
    out << "[OK] Weather updated and verified safe for flight operations.\n";
}

void AirportCLI::runSecurityScreeningInteractive(std::istream& in, std::ostream& out) {
    std::size_t paxIdx = 0;
    double bagWeightKg = 0.0;
    int liquidMl = 0;
    double metalGrams = 0.0;
    out << "Enter Passenger index, HandLuggageWeight(kg), LiquidVolume(ml), Metal(grams): ";
    in >> paxIdx >> bagWeightKg >> liquidMl >> metalGrams;
    if (paxIdx >= passengers_.size()) {
        out << "[ERROR] Invalid passenger index.\n";
        return;
    }
    HandLuggage bag(bagWeightKg, liquidMl > 0, liquidMl, true);
    XRayScanner scanner("XRAY-1", kDefaultScannerSensitivity, true);
    MetalDetector detector("MD-1", kDefaultMetalThresholdGrams, true);
    SecurityCheckpoint cp("CP-MAIN", "Zone-A", true);
    cp.processPassengerScreening(passengers_[paxIdx], bag, scanner, detector, metalGrams);
    out << "[OK] Passenger " << passengers_[paxIdx].getFullName() << " cleared security.\n";
}

void AirportCLI::manageFinanceInteractive(std::istream& in, std::ostream& out) {
    std::size_t fltIdx = 0;
    int stdMeals = 0;
    int bizMeals = 0;
    double reserveAlloc = 0.0;
    out << "Enter Flight index, StandardMeals, BusinessMeals, ReserveAllocation($): ";
    in >> fltIdx >> stdMeals >> bizMeals >> reserveAlloc;
    if (fltIdx >= flights_.size()) {
        out << "[ERROR] Invalid flight index.\n";
        return;
    }
    CateringOrder order("CAT-CLI", flights_[fltIdx], stdMeals, bizMeals);
    finance_.payCateringExpense(order, kStandardMealPriceUsd, kBusinessMealPriceUsd);
    finance_.allocateToReserve(reserveAlloc);
    out << "[OK] Finance updated | Net Profit: $" << finance_.calculateNetProfitUsd()
        << " | Reserve: $" << finance_.getReserveFundUsd() << "\n";
}

bool AirportCLI::dispatchChoice(int choice, std::istream& in, std::ostream& out) {
    switch (choice) {
        case 1: displayAllData(out); break;
        case 2: addPassengerInteractive(in, out); break;
        case 3: checkInAndIssueTicketInteractive(in, out); break;
        case 4: cancelTicketInteractive(in, out); break;
        case 5: addAircraftInteractive(in, out); break;
        case 6: modifyAircraftStatusInteractive(in, out); break;
        case 7: addFlightInteractive(in, out); break;
        case 8: updateFlightStatusInteractive(in, out); break;
        case 9: updateWeatherInteractive(in, out); break;
        case 10: runSecurityScreeningInteractive(in, out); break;
        case 11: manageFinanceInteractive(in, out); break;
        default: out << "Invalid menu choice.\n"; return false;
    }
    return true;
}

bool AirportCLI::processMenuChoice(int choice, std::istream& in, std::ostream& out) {
    if (choice == 0) {
        isRunning_ = false;
        out << "Exiting Airport Management System.\n";
        return false;
    }
    try {
        if (dispatchChoice(choice, in, out)) {
            ++executedOperationsCount_;
        }
    } catch (const AirportException& ex) {
        out << "[DOMAIN ERROR " << ex.getErrorCode() << "] " << ex.what() << "\n";
    }
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
        processMenuChoice(choice, in, out);
    }
}

bool AirportCLI::getIsRunning() const { return isRunning_; }
int AirportCLI::getExecutedOperationsCount() const { return executedOperationsCount_; }
std::size_t AirportCLI::getPassengersCount() const { return passengers_.size(); }
std::size_t AirportCLI::getTicketsCount() const { return tickets_.size(); }
std::size_t AirportCLI::getAircraftsCount() const { return aircrafts_.size(); }
std::size_t AirportCLI::getFlightsCount() const { return flights_.size(); }

}
