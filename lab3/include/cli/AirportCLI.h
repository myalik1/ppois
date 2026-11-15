#pragma once
#include <iostream>
#include <string>

namespace airport {

class AirportCLI {
private:
    bool isRunning_;
    int executedOperationsCount_;

    void printMenu(std::ostream& out) const;
    void handlePassengerAndTicketWorkflow(std::ostream& out);
    void handleAircraftAndCrewWorkflow(std::ostream& out);
    void handleSecurityAndCustomsWorkflow(std::ostream& out);
    void handleFlightAndServicesWorkflow(std::ostream& out);

public:
    AirportCLI();

    bool processMenuChoice(int choice, std::ostream& out);
    void runInteractiveLoop(std::istream& in, std::ostream& out);

    bool getIsRunning() const;
    int getExecutedOperationsCount() const;
};

}
