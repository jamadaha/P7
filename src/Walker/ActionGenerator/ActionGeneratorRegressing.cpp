#include "ActionGeneratorRegressing.hpp"

using namespace std;

vector<PDDLActionInstance> ActionGeneratorRegressing::GenerateActions(const PDDLState *state) {
    vector<PDDLActionInstance> legalActions;

    totalActions += legalActions.size();
    return legalActions;
}