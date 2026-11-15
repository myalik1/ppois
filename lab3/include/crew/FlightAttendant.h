#pragma once
#include <string>
#include "MedicalCertificate.h"

namespace airport {

class FlightAttendant {
private:
    std::string employeeId_;
    std::string fullName_;
    int experienceYears_;
    bool isSeniorPurser_;
    bool emergencyTrainingPassed_;

public:
    FlightAttendant(const std::string& employeeId,
                    const std::string& fullName,
                    int experienceYears,
                    bool isSeniorPurser,
                    bool emergencyTrainingPassed);

    bool isReadyForFlight(const MedicalCertificate& medical, int currentYear) const;
    void promoteToPurser();
    void completeSafetyDrill();

    const std::string& getEmployeeId() const;
    const std::string& getFullName() const;
    int getExperienceYears() const;
    bool getIsSeniorPurser() const;
    bool getEmergencyTrainingPassed() const;
};

}
