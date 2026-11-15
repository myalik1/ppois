# Лабораторная работа №3. Система Аэропорт (Airport System)

## Описание классов предметной области

Формат строки: `Класс | число полей | число методов | связанные классы`.

| Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|
| Passport | 5 | 3 | — |
| Visa | 5 | 3 | Passport |
| LoyaltyCard | 4 | 4 | — |
| BaggageTag | 4 | 3 | — |
| BaggageItem | 5 | 4 | BaggageTag |
| HandLuggage | 4 | 3 | — |
| Passenger | 5 | 4 | Passport, Visa, LoyaltyCard, BaggageItem, HandLuggage |
| LostBaggageRecord | 5 | 3 | Passenger, BaggageTag |
| Seat | 5 | 3 | — |
| FareRule | 5 | 3 | — |
| Ticket | 5 | 4 | Passenger, Seat, FareRule, LoyaltyCard |
| BoardingPass | 5 | 3 | Ticket, Seat, Passenger |
| Booking | 5 | 4 | Ticket, Passenger |
| PaymentTransaction | 5 | 3 | Booking |
| Invoice | 5 | 3 | Booking, PaymentTransaction |
| Engine | 5 | 4 | — |
| FuelTank | 4 | 4 | — |
| CabinLayout | 4 | 3 | Seat |
| AvionicsSystem | 4 | 3 | — |
| LandingGear | 4 | 3 | — |
| Aircraft | 5 | 4 | Engine, FuelTank, CabinLayout, AvionicsSystem, LandingGear |
| MaintenanceLog | 5 | 3 | Aircraft |
| DeicingUnit | 4 | 3 | Aircraft |
| PilotLicense | 5 | 3 | — |
| MedicalCertificate | 4 | 3 | — |
| Pilot | 5 | 4 | PilotLicense, MedicalCertificate, Aircraft |
| FlightAttendant | 5 | 3 | MedicalCertificate |
| GroundTechnician | 5 | 3 | Aircraft, Engine, LandingGear, MaintenanceLog |
| CrewShift | 5 | 3 | Pilot, FlightAttendant |
| CrewRoster | 4 | 4 | Pilot, FlightAttendant, CrewShift |
| WeatherCondition | 5 | 3 | — |
| Runway | 5 | 4 | Aircraft, WeatherCondition |
| Gate | 5 | 3 | Aircraft |
| FlightRoute | 5 | 3 | — |
| Flight | 6 | 5 | Aircraft, FlightRoute, Gate, Runway, CrewRoster, BoardingPass |
| FlightSchedule | 4 | 4 | Flight, WeatherCondition |
| ControlTower | 5 | 4 | Runway, Flight, WeatherCondition |
| RadarContact | 5 | 3 | Flight |
| SecurityBadge | 4 | 3 | — |
| XRayScanner | 4 | 3 | HandLuggage |
| MetalDetector | 4 | 3 | Passenger |
| SecurityCheckpoint | 5 | 4 | Passenger, HandLuggage, XRayScanner, MetalDetector |
| CustomsDeclaration | 5 | 3 | Passenger, BaggageItem |
| BorderControl | 4 | 3 | Passenger, Passport, Visa, SecurityBadge |
| SecurityIncident | 5 | 3 | SecurityCheckpoint, SecurityBadge |
| CateringOrder | 5 | 3 | Flight |
| FuelTruck | 4 | 3 | FuelTank |
| BaggageConveyor | 5 | 4 | BaggageItem |
| ShuttleBus | 5 | 4 | Gate |
| VipLounge | 5 | 3 | Passenger, LoyaltyCard, Ticket |
| ParkingLot | 5 | 4 | — |
| AirportFinance | 5 | 4 | Invoice, CateringOrder, PaymentTransaction |

### Исключения (12)

- AirportException
- InvalidPassportException
- VisaExpiredException
- BaggageOverweightException
- InvalidTicketException
- FlightOverbookedException
- AircraftMaintenanceException
- InsufficientFuelException
- RunwayOccupiedException
- WeatherHazardException
- SecurityBreachException
- InsufficientFundsException

### Итоговая статистика проекта

| Показатель | Значение |
|---|---|
| Классы | 52 |
| Поля | 245 |
| Поведения | 176 |
| Ассоциации | 81 |
| Исключения | 12 |
