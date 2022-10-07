cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)

project(P7 VERSION 0.1.0)

# Add source to this project's executable.
set(SOURCES 
    # PDDL Parser
	"src/PDDLParser/action.cc" "src/PDDLParser/action.hh" "src/PDDLParser/pddldriver.cc" "src/PDDLParser/pddldriver.hh" "src/PDDLParser/domain.cc" "src/PDDLParser/domain.hh" "src/PDDLParser/location.hh" "src/PDDLParser/pddllex.yy.cc" "src/PDDLParser/pddlparser.tab.cc" "src/PDDLParser/pddlparser.tab.hh" "src/PDDLParser/position.hh" "src/PDDLParser/predicate.cc" "src/PDDLParser/predicate.hh" "src/PDDLParser/problem.cc" "src/PDDLParser/problem.hh" "src/PDDLParser/stack.hh"
	# Config
	"src/Config/config.cpp"
	# Fast Downward
	"src/DownwardRunner/DownwardRunner.cpp"
	# SAS Parser
	"src/SASParser/SASParser.h" "src/SASParser/SASParser.cpp"
	# Time Report
	"src/Report.hh"
	# PDDL Code Generator
	"src/PDDLCodeGenerator/PDDLCodeGenerator.h" "src/PDDLCodeGenerator/PDDLCodeGenerator.cpp" "src/PDDLCodeGenerator/PDDLDomainCodeGenerator.h" "src/PDDLCodeGenerator/PDDLDomainCodeGenerator.cpp" "src/PDDLCodeGenerator/PDDLProblemCodeGenerator.h" "src/PDDLCodeGenerator/PDDLProblemCodeGenerator.cpp" "src/PDDLCodeGenerator/BasePDDLCodeGenerator.h" "src/PDDLCodeGenerator/BasePDDLCodeGenerator.cpp" 
	# SAS Code Generator
	"src/SASCodeGenerator/SASCodeGenerator.h" "src/SASCodeGenerator/SASCodeGenerator.cpp" 
	# File Verifier
	"src/FileVerifier/FileVerifier.h" "src/FileVerifier/FileVerifier.cpp" 
	# Helpers
	"src/Helpers/StringHelper.h" "src/Helpers/StringHelper.cpp" 
	"src/Helpers/FileHelper.h" "src/Helpers/FileHelper.cpp" 
	# Reformulators
	"src/Reformulators/BaseReformulator.h" "src/Reformulators/SameOutputReformulator.cpp" 
	# Common Interface
	"src/CommonInterface/CommonInterface.h" "src/CommonInterface/CommonInterface.cpp" "src/Reformulators/SameOutputReformulator.h" 
	# Plan Validator
	"src/PlanValidators/PlanValidator.h" "src/PlanValidators/PlanValidator.cpp" 
	# Heuristics
	"src/Heuristics/BaseHeuristics.hh" "src/Heuristics/RandomHeuristic.hh" "src/Heuristics/Contexts/BaseContext.h" "src/Heuristics/Contexts/PDDLContext.h"
	# PDDL Types
	"src/PDDLTypes/PDDLAction.hpp" "src/PDDLTypes/PDDLArg.hpp" "src/PDDLTypes/PDDLLiteral.hpp" "src/PDDLTypes/PDDLDomain.hpp" "src/PDDLTypes/PDDLPredicate.hpp" "src/PDDLTypes/PDDLProblem.hpp" "src/PDDLTypes/PDDLType.hpp" "src/PDDLTypes/PDDLInstance.hpp" "src/PDDLTypes/PDDLState.hpp"
	# Something new

)
add_executable (P7 "src/P7.cpp" ${SOURCES})
target_include_directories(P7 PRIVATE "PDDLParser")

file(COPY Data DESTINATION ${CMAKE_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(Test/CMakeLists.txt)