#ifndef PDDL_PARSER
#define PDDL_PARSER

#include <string>

#include "../PDDL/Instance.hh"
#include "../PDDL/Parsers/ExternalParser/pddldriver.hh"
#include "Converter.hh"

class ExternalParser {
public:
    PDDL::Instance* Parse(const std::string& domain, const std::string& problem);
};

#endif
