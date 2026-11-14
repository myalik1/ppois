#include "../../include/crew/CrewShift.h"

namespace airport {

namespace {
const int kMaxLegalShiftHours = 12;
const double kNightBonusMultiplier = 1.25;
const double kPurserBonusUsd = 40.0;
}

CrewShift::CrewShift(const std::string& shiftId,
                     int startHour,
                     int durationHours,
                     bool isNightShift,
                     bool isCompleted)
    : shiftId_(shiftId),
      startHour_(startHour),
      durationHours_(durationHours),
      isNightShift_(isNightShift),
      isCompleted_(isCompleted) {}

bool CrewShift::validateDutyTimeLimit() const {
    return durationHours_ > 0 && durationHours_ <= kMaxLegalShiftHours;
}

void CrewShift::completeShift(Pilot& captain, Pilot& firstOfficer) {
    if (validateDutyTimeLimit() && !isCompleted_) {
        captain.logCompletedFlight(static_cast<double>(durationHours_));
        firstOfficer.logCompletedFlight(static_cast<double>(durationHours_));
        isCompleted_ = true;
    }
}

double CrewShift::calculateShiftAllowanceUsd(const FlightAttendant& attendant,
                                             double hourlyRate) const {
    double basePay = static_cast<double>(durationHours_) * hourlyRate;
    if (isNightShift_) {
        basePay *= kNightBonusMultiplier;
    }
    if (attendant.getIsSeniorPurser()) {
        basePay += kPurserBonusUsd;
    }
    return basePay;
}

const std::string& CrewShift::getShiftId() const { return shiftId_; }
int CrewShift::getStartHour() const { return startHour_; }
int CrewShift::getDurationHours() const { return durationHours_; }
bool CrewShift::getIsNightShift() const { return isNightShift_; }
bool CrewShift::getIsCompleted() const { return isCompleted_; }

}
