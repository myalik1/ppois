#pragma once
#include <string>
#include "PilotLicense.h"
#include "MedicalCertificate.h"
#include "../aircraft/Aircraft.h"

namespace airport {

class Pilot {
private:
    std::string employeeId_;
    std::string fullName_;
    std::string rank_;
    double totalFlightHours_;
    double monthlyDutyHours_;

public:
    Pilot(const std::string& employeeId,
          const std::string& fullName,
          const std::string& rank,
          double totalFlightHours,
          double monthlyDutyHours = 0.0);

    bool isQualifiedForAircraft(const PilotLicense& license,
                                const MedicalCertificate& medical,
                                const Aircraft& aircraft,
                                int currentYear) const;
    void logCompletedFlight(double durationHours);
    bool canPromoteToCaptain() const;
    void resetMonthlyDutyHours();

    const std::string& getEmployeeId() const;
    const std::string& getFullName() const;
    const std::string& getRank() const;
    double getTotalFlightHours() const;
    double getMonthlyDutyHours() const;
};

}
