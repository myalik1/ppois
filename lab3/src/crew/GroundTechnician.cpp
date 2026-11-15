#include "../../include/crew/GroundTechnician.h"
#include "../../include/exceptions/AirportExceptions.h"

namespace airport {

namespace {
const int kHeavyMaintenanceMinLevel = 3;
}

GroundTechnician::GroundTechnician(const std::string& technicianId,
                                   const std::string& specialization,
                                   int certificationLevel,
                                   int completedRepairs,
                                   bool isOnShift)
    : technicianId_(technicianId),
      specialization_(specialization),
      certificationLevel_(certificationLevel),
      completedRepairs_(completedRepairs),
      isOnShift_(isOnShift) {}

void GroundTechnician::inspectAndApproveAircraft(const Engine& engine,
                                                 const LandingGear& gear,
                                                 MaintenanceLog& log) {
    if (!isOnShift_) {
        throw AircraftMaintenanceException("Technician is off shift");
    }
    if (engine.needsOverhaul()) {
        throw AircraftMaintenanceException("Technician rejected engine due to overhaul limit");
    }
    gear.inspectLandingGear();
    log.signOffMaintenance();
    ++completedRepairs_;
}

void GroundTechnician::reportTechnicalIssue(Aircraft& aircraft,
                                            MaintenanceLog& log,
                                            const std::string& issue) {
    if (!technicianId_.empty()) {
        log.reportDefect(aircraft, issue);
    }
}

bool GroundTechnician::isCertifiedForHeavyMaintenance() const {
    return certificationLevel_ >= kHeavyMaintenanceMinLevel;
}

const std::string& GroundTechnician::getTechnicianId() const { return technicianId_; }
const std::string& GroundTechnician::getSpecialization() const { return specialization_; }
int GroundTechnician::getCertificationLevel() const { return certificationLevel_; }
int GroundTechnician::getCompletedRepairs() const { return completedRepairs_; }
bool GroundTechnician::getIsOnShift() const { return isOnShift_; }

}
