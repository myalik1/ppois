#include "../../include/crew/Pilot.h"

namespace airport {

namespace {
const double kMaxMonthlyDutyHours = 100.0;
const double kCaptainPromotionHours = 3000.0;
}

Pilot::Pilot(const std::string& employeeId,
             const std::string& fullName,
             const std::string& rank,
             double totalFlightHours,
             double monthlyDutyHours)
    : employeeId_(employeeId),
      fullName_(fullName),
      rank_(rank),
      totalFlightHours_(totalFlightHours),
      monthlyDutyHours_(monthlyDutyHours) {}

bool Pilot::isQualifiedForAircraft(const PilotLicense& license,
                                   const MedicalCertificate& medical,
                                   const Aircraft& aircraft,
                                   int currentYear) const {
    bool docsValid = license.isLicenseValid(currentYear) &&
                     medical.validateMedicalFitness(currentYear);
    bool typeMatch = license.matchesAircraftModel(aircraft.getModelName());
    return docsValid && typeMatch && monthlyDutyHours_ < kMaxMonthlyDutyHours;
}

void Pilot::logCompletedFlight(double durationHours) {
    if (durationHours > 0.0) {
        totalFlightHours_ += durationHours;
        monthlyDutyHours_ += durationHours;
    }
}

bool Pilot::canPromoteToCaptain() const {
    return rank_ != "CAPTAIN" && totalFlightHours_ >= kCaptainPromotionHours;
}

void Pilot::resetMonthlyDutyHours() {
    monthlyDutyHours_ = 0.0;
}

const std::string& Pilot::getEmployeeId() const { return employeeId_; }
const std::string& Pilot::getFullName() const { return fullName_; }
const std::string& Pilot::getRank() const { return rank_; }
double Pilot::getTotalFlightHours() const { return totalFlightHours_; }
double Pilot::getMonthlyDutyHours() const { return monthlyDutyHours_; }

}
