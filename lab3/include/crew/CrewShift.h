#pragma once
#include <string>
#include "Pilot.h"
#include "FlightAttendant.h"

namespace airport {

class CrewShift {
private:
    std::string shiftId_;
    int startHour_;
    int durationHours_;
    bool isNightShift_;
    bool isCompleted_;

public:
    CrewShift(const std::string& shiftId,
              int startHour,
              int durationHours,
              bool isNightShift,
              bool isCompleted = false);

    bool validateDutyTimeLimit() const;
    void completeShift(Pilot& captain, Pilot& firstOfficer);
    double calculateShiftAllowanceUsd(const FlightAttendant& attendant, double hourlyRate) const;

    const std::string& getShiftId() const;
    int getStartHour() const;
    int getDurationHours() const;
    bool getIsNightShift() const;
    bool getIsCompleted() const;
};

}
