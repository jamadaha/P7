#include <vector>
#include <iostream>

#include "SAS_Parser.h"

int main(int, char**) {
    std::vector<Action> actions = SAS_Parser().Parse("sas_plan");
    printf("Done\n");
}
