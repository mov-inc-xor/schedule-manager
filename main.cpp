#include <iostream>

#include "Terminal.h"

int main() {
    Terminal terminal(std::cin, std::cout);
    terminal.start();
    return 0;
}
