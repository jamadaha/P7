#ifndef MACROCANDIDATE_HH
#define MACROCANDIDATE_HH

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "EntanglementOccurance.hh"

struct MacroCandidate {
    std::vector<std::vector<PDDLActionInstance*>> Entanglements;
    int Occurance;
    int BetweenDifferentPaths;
    double Quality = 1;

    MacroCandidate(std::vector<std::vector<PDDLActionInstance*>> entanglements, int occurance, int betweenPaths) : Entanglements(entanglements), Occurance(occurance), BetweenDifferentPaths(betweenPaths) {};
};

#endif
