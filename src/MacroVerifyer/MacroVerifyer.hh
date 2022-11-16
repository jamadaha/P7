#ifndef MACRO_VERIFYER
#define MACRO_VERIFYER

#include <vector>
#include "../MacroGenerator/Macro.hh"

class MacroVerifyer {
public:
    bool VerifyMacros(std::vector<Macro>* macros);
};

#endif
