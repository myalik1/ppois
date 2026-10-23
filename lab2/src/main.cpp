#include "../include/cli/ConsoleMenu.h"
#include <iostream>

int main() {
    docflow::ConsoleMenu menu;
    menu.runInteractiveLoop(std::cin, std::cout);
    return 0;
}
