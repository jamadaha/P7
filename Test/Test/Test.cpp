#include <stdexcept>
#include <string>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc == 1)
        exit(EXIT_SUCCESS);
    else
        throw std::logic_error("Incorrect argument count | Expected " + std::to_string(1) + " - Actual " + std::to_string(argc));
}