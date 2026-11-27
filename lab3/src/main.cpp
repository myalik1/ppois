#include <iostream>
#include "../include/cli/AirportCLI.h"

int main() {
    airport::AirportCLI cli;
    cli.runInteractiveLoop(std::cin, std::cout);
    return 0;
}
