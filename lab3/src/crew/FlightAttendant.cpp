#include "../../include/crew/FlightAttendant.h"

namespace airport {

namespace {
const int kMinPurserExperienceYears = 3;
}

FlightAttendant::FlightAttendant(const std::string& employeeId,
                                 const std::string& fullName,
                                 int experienceYears,
                                 bool isSeniorPurser,
                                 bool emergencyTrainingPassed)
    : employeeId_(employeeId),
      fullName_(fullName),
      experienceYears_(experienceYears),
      isSeniorPurser_(isSeniorPurser),
      emergencyTrainingPassed_(emergencyTrainingPassed) {}

bool FlightAttendant::isReadyForFlight(const MedicalCertificate& medical, int currentYear) const {
    return emergencyTrainingPassed_ && medical.validateMedicalFitness(currentYear);
}

void FlightAttendant::promoteToPurser() {
    if (experienceYears_ >= kMinPurserExperienceYears && emergencyTrainingPassed_) {
        isSeniorPurser_ = true;
    }
}

void FlightAttendant::completeSafetyDrill() {
    emergencyTrainingPassed_ = true;
}

const std::string& FlightAttendant::getEmployeeId() const { return employeeId_; }
const std::string& FlightAttendant::getFullName() const { return fullName_; }
int FlightAttendant::getExperienceYears() const { return experienceYears_; }
bool FlightAttendant::getIsSeniorPurser() const { return isSeniorPurser_; }
bool FlightAttendant::getEmergencyTrainingPassed() const { return emergencyTrainingPassed_; }

}
