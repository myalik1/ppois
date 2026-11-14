#pragma once
#include <string>
#include "../aircraft/Aircraft.h"
#include "../aircraft/Engine.h"
#include "../aircraft/LandingGear.h"
#include "../aircraft/MaintenanceLog.h"

namespace airport {

class GroundTechnician {
private:
    std::string technicianId_;
    std::string specialization_;
    int certificationLevel_;
    int completedRepairs_;
    bool isOnShift_;

public:
    GroundTechnician(const std::string& technicianId,
                     const std::string& specialization,
                     int certificationLevel,
                     int completedRepairs = 0,
                     bool isOnShift = true);

    void inspectAndApproveAircraft(const Engine& engine,
                                   const LandingGear& gear,
                                   MaintenanceLog& log);
    void reportTechnicalIssue(Aircraft& aircraft,
                              MaintenanceLog& log,
                              const std::string& issue);
    bool isCertifiedForHeavyMaintenance() const;

    const std::string& getTechnicianId() const;
    const std::string& getSpecialization() const;
    int getCertificationLevel() const;
    int getCompletedRepairs() const;
    bool getIsOnShift() const;
};

}
