#pragma once
#include <stdexcept>
#include <string>

namespace airport {

class AirportException : public std::runtime_error {
private:
    int errorCode_;

public:
    explicit AirportException(const std::string& message, int errorCode = 1000);
    int getErrorCode() const noexcept;
};

class InvalidPassportException : public AirportException {
public:
    explicit InvalidPassportException(const std::string& message);
};

class VisaExpiredException : public AirportException {
public:
    explicit VisaExpiredException(const std::string& message);
};

class BaggageOverweightException : public AirportException {
public:
    explicit BaggageOverweightException(const std::string& message);
};

class InvalidTicketException : public AirportException {
public:
    explicit InvalidTicketException(const std::string& message);
};

class FlightOverbookedException : public AirportException {
public:
    explicit FlightOverbookedException(const std::string& message);
};

class AircraftMaintenanceException : public AirportException {
public:
    explicit AircraftMaintenanceException(const std::string& message);
};

class InsufficientFuelException : public AirportException {
public:
    explicit InsufficientFuelException(const std::string& message);
};

class RunwayOccupiedException : public AirportException {
public:
    explicit RunwayOccupiedException(const std::string& message);
};

class WeatherHazardException : public AirportException {
public:
    explicit WeatherHazardException(const std::string& message);
};

class SecurityBreachException : public AirportException {
public:
    explicit SecurityBreachException(const std::string& message);
};

class InsufficientFundsException : public AirportException {
public:
    explicit InsufficientFundsException(const std::string& message);
};

}
