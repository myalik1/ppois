#include "../../include/crew/CrewRoster.h"

namespace airport {

namespace {
const int kMinCockpitPilots = 2;
const int kPassengersPerAttendant = 50;
}

CrewRoster::CrewRoster(const std::string& rosterId,
                       int assignedPilotsCount,
                       int assignedAttendantsCount,
                       bool isRosterComplete)
    : rosterId_(rosterId),
      assignedPilotsCount_(assignedPilotsCount),
      assignedAttendantsCount_(assignedAttendantsCount),
      isRosterComplete_(isRosterComplete) {}

void CrewRoster::assignPilotToRoster(const Pilot& pilot) {
    if (!pilot.getEmployeeId().empty()) {
        ++assignedPilotsCount_;
    }
}

void CrewRoster::assignAttendantToRoster(const FlightAttendant& attendant) {
    if (attendant.getEmergencyTrainingPassed()) {
        ++assignedAttendantsCount_;
    }
}

bool CrewRoster::verifyMinimumCrewRequirements(int passengerCapacity) {
    int requiredAttendants = (passengerCapacity + kPassengersPerAttendant - 1) / kPassengersPerAttendant;
    if (requiredAttendants < 1) {
        requiredAttendants = 1;
    }
    isRosterComplete_ = (assignedPilotsCount_ >= kMinCockpitPilots) &&
                        (assignedAttendantsCount_ >= requiredAttendants);
    return isRosterComplete_;
}

bool CrewRoster::validateRosterForShift(const CrewShift& shift) const {
    return isRosterComplete_ && shift.validateDutyTimeLimit();
}

const std::string& CrewRoster::getRosterId() const { return rosterId_; }
int CrewRoster::getAssignedPilotsCount() const { return assignedPilotsCount_; }
int CrewRoster::getAssignedAttendantsCount() const { return assignedAttendantsCount_; }
bool CrewRoster::getIsRosterComplete() const { return isRosterComplete_; }

}
