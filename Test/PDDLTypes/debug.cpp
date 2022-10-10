#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/PDDLTypes/PDDLDomain.hpp"
#include "../../src/PDDLParser/pddldriver.hh"

using namespace std;

const string domainFile = "./TestFiles/domain.pddl";
const string exDomainName = "blocksworld";
const vector<string> exDomainReq = {":strips", ":equality"};

int main(){
    PDDLDriver driver = PDDLDriver();
    driver.parse(domainFile);
    PDDLDomain domain = PDDLDomain(driver.domain);
}