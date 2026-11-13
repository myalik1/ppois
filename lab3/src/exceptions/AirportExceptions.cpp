#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const int kInvalidPassportCode = 1001;
const int kVisaExpiredCode = 1002;
const int kBaggageOverweightCode = 1003;
const int kInvalidTicketCode = 1004;
const int kFlightOverbookedCode = 1005;
const int kAircraftMaintenanceCode = 1006;
const int kInsufficientFuelCode = 1007;
const int kRunwayOccupiedCode = 1008;
const int kWeatherHazardCode = 1009;
const int kSecurityBreachCode = 1010;
const int kInsufficientFundsCode = 1011;
}

AirportException::AirportException(const std::string& message, int errorCode)
    : std::runtime_error(message), errorCode_(errorCode) {}

int AirportException::getErrorCode() const noexcept {
    return errorCode_;
}

InvalidPassportException::InvalidPassportException(const std::string& message)
    : AirportException("Passport Error: " + message, kInvalidPassportCode) {}

VisaExpiredException::VisaExpiredException(const std::string& message)
    : AirportException("Visa Error: " + message, kVisaExpiredCode) {}

BaggageOverweightException::BaggageOverweightException(const std::string& message)
    : AirportException("Baggage Error: " + message, kBaggageOverweightCode) {}

InvalidTicketException::InvalidTicketException(const std::string& message)
    : AirportException("Ticket Error: " + message, kInvalidTicketCode) {}

FlightOverbookedException::FlightOverbookedException(const std::string& message)
    : AirportException("Overbooking Error: " + message, kFlightOverbookedCode) {}

AircraftMaintenanceException::AircraftMaintenanceException(const std::string& message)
    : AirportException("Maintenance Error: " + message, kAircraftMaintenanceCode) {}

InsufficientFuelException::InsufficientFuelException(const std::string& message)
    : AirportException("Fuel Error: " + message, kInsufficientFuelCode) {}

RunwayOccupiedException::RunwayOccupiedException(const std::string& message)
    : AirportException("Runway Error: " + message, kRunwayOccupiedCode) {}

WeatherHazardException::WeatherHazardException(const std::string& message)
    : AirportException("Weather Error: " + message, kWeatherHazardCode) {}

SecurityBreachException::SecurityBreachException(const std::string& message)
    : AirportException("Security Error: " + message, kSecurityBreachCode) {}

InsufficientFundsException::InsufficientFundsException(const std::string& message)
    : AirportException("Payment Error: " + message, kInsufficientFundsCode) {}

}
