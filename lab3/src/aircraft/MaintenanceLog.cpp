#include "../../include/aircraft/MaintenanceLog.h"

namespace airport {

namespace {
const int kMaxInspectionAgeYears = 1;
}
MaintenanceLog::MaintenanceLog(const std::string& recordId,
                               const Aircraft& aircraft,
                               const std::string& description,
                               int inspectionYear,
                               bool isClearedToFly)
    : recordId_(recordId),
      tailNumber_(aircraft.getTailNumber()),
      description_(description),
      inspectionYear_(inspectionYear),
      isClearedToFly_(isClearedToFly) {}

void MaintenanceLog::signOffMaintenance() {
    isClearedToFly_ = true;
}

void MaintenanceLog::reportDefect(Aircraft& aircraft, const std::string& defectDetails) {
    description_ = defectDetails;
    isClearedToFly_ = false;
    aircraft.groundAircraft();
}

bool MaintenanceLog::isInspectionCurrent(int currentYear) const {
    return isClearedToFly_ && (currentYear - inspectionYear_) <= kMaxInspectionAgeYears;
}

const std::string& MaintenanceLog::getRecordId() const { return recordId_; }
const std::string& MaintenanceLog::getTailNumber() const { return tailNumber_; }
const std::string& MaintenanceLog::getDescription() const { return description_; }
int MaintenanceLog::getInspectionYear() const { return inspectionYear_; }
bool MaintenanceLog::getIsClearedToFly() const { return isClearedToFly_; }

}
