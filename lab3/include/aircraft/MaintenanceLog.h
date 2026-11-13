#pragma once
#include <string>
#include "Aircraft.h"

namespace airport {

class MaintenanceLog {
private:
    std::string recordId_;
    std::string tailNumber_;
    std::string description_;
    int inspectionYear_;
    bool isClearedToFly_;

public:
    MaintenanceLog(const std::string& recordId,
                   const Aircraft& aircraft,
                   const std::string& description,
                   int inspectionYear,
                   bool isClearedToFly = false);

    void signOffMaintenance();
    void reportDefect(Aircraft& aircraft, const std::string& defectDetails);
    bool isInspectionCurrent(int currentYear) const;

    const std::string& getRecordId() const;
    const std::string& getTailNumber() const;
    const std::string& getDescription() const;
    int getInspectionYear() const;
    bool getIsClearedToFly() const;
};

}
