#ifndef MACRO_VERIFYER
#define MACRO_VERIFYER

#include <vector>
#include "../MacroGenerator/Macro.hh"

struct BadMacro {
    std::string Reason = "";
    Macro macro;

    BadMacro(Macro macro, std::string reason) : macro(macro), Reason(reason) {};
};

class MacroVerifyer {
public:
    std::vector<BadMacro> VerifyMacros(std::vector<Macro>* macros, PDDLDomain* domain);
};

#endif
