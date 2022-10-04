#include <catch2/catch_test_macros.hpp>
#include "../../src/SASCodeGenerator/SASCodeGenerator.h"
#include <iostream>
using namespace std;

const string tag = "SASCodeGenerator ";

TEST_CASE(tag + "Parameters"){
    cout << "hello" << endl;
    //Generator and parser
    SASCodeGenerator gen;
    SASParser parser;
    
    //test setup
    SASAction act = SASAction("task", {"p1", "p2"});
    string test = "(task p1 p2)\n; cost = 1 (general cost)";
    string fname = "./TestFiles/params.txt";

    SASPlan plan = parser.Parse(test);
    
    gen.GenerateCode(plan, fname);

    ifstream fptr(fname);
    string fcontent;
    if (fptr) {
        ostringstream ss;
        ss << fptr.rdbuf();
        fcontent = ss.str();
    }
    //assertions
    cout << fcontent;
    cout << test;
    REQUIRE(fcontent == test);
}