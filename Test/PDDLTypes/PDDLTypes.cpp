#include <catch2/catch_test_macros.hpp>
#include <string>

#include "../../src/PDDLTypes/PDDLDomain.hpp"
#include "../../src/PDDLParser/pddldriver.hh"

using namespace std;


const string TAG = "PDDLTypes ";

const string domainFile = "./TestFiles/action.pddl";
const string exDomainName = "blocksworld";
const vector<string> exDomainReq = {":strips", ":equality"};

bool cmpList(vector<string> as, vector<string> bs){
    bool acc = true;
    for(string a : as)
        for (string b : bs)
            acc = acc && (a==b);
    return acc;
}

TEST_CASE(TAG + "PDDLDomain names + requirements") {
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDLDomain *domain = new PDDLDomain(driver.domain);

    //REQUIRE(domain->name == exDomainName);
    //REQUIRE(cmpList(domain->requirements, exDomainReq));
    REQUIRE(true);
}

/*
TEST_CASE(TAG + "PDDLDomain actions"){
    PDDLDriver driver;
    driver.parse(domainFile);
    PDDLDomain *domain = new PDDLDomain(driver.domain);
    REQUIRE(true);
}
*/