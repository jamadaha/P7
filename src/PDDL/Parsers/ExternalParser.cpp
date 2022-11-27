#include "ExternalParser.hh"

PDDL::Instance* ExternalParser::Parse(const std::string& domainFile, const std::string& problemFile) {
	PDDLDriver driver;
	if (driver.parse(domainFile))
		throw std::invalid_argument("Invalid domain file!");
	if (driver.parse(problemFile))
		throw std::invalid_argument("Invalid problem file!");

	static PDDL::Domain domain = Converter::Convert(driver.domain);
	static PDDL::Problem problem = Converter::Convert(&domain, driver.problem);

	return new PDDL::Instance(&domain, &problem);
}