#pragma once
#include <string>
#include "Pilot.h"
#include "FlightAttendant.h"
#include "CrewShift.h"

namespace airport {

class CrewRoster {
private:
    std::string rosterId_;
    int assignedPilotsCount_;
    int assignedAttendantsCount_;
    bool isRosterComplete_;

public:
    CrewRoster(const std::string& rosterId,
               int assignedPilotsCount = 0,
               int assignedAttendantsCount = 0,
               bool isRosterComplete = false);

    void assignPilotToRoster(const Pilot& pilot);
    void assignAttendantToRoster(const FlightAttendant& attendant);
    bool verifyMinimumCrewRequirements(int passengerCapacity);
    bool validateRosterForShift(const CrewShift& shift) const;

    const std::string& getRosterId() const;
    int getAssignedPilotsCount() const;
    int getAssignedAttendantsCount() const;
    bool getIsRosterComplete() const;
};

}
