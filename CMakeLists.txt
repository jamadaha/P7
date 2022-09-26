cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)

project(P7 VERSION 0.1.0)

include(CTest)
enable_testing()

# Add source to this project's executable.
set(SOURCES 
	"src/PDDLParser/action.cc" "src/PDDLParser/action.hh" 
	"src/PDDLParser/pddldriver.cc" "src/PDDLParser/pddldriver.hh"
	"src/PDDLParser/domain.cc" "src/PDDLParser/domain.hh"
	"src/PDDLParser/location.hh"
	"src/PDDLParser/pddllex.yy.cc"
	"src/PDDLParser/pddlparser.tab.cc" "src/PDDLParser/pddlparser.tab.hh"
	"src/PDDLParser/position.hh"
	"src/PDDLParser/predicate.cc" "src/PDDLParser/predicate.hh"
	"src/PDDLParser/problem.cc" "src/PDDLParser/problem.hh"
	"src/PDDLParser/stack.hh"

	"src/SASParser/SASParser.h" "src/SASParser/SASParser.cpp"
	"src/PDDLCodeGenerator/PDDLCodeGenerator.h" "src/PDDLCodeGenerator/PDDLCodeGenerator.cpp" "src/PDDLCodeGenerator/PDDLDomainCodeGenerator.h" "src/PDDLCodeGenerator/PDDLDomainCodeGenerator.cpp" "src/PDDLCodeGenerator/PDDLProblemCodeGenerator.h" "src/PDDLCodeGenerator/PDDLProblemCodeGenerator.cpp" "src/PDDLCodeGenerator/BasePDDLCodeGenerator.h" "src/PDDLCodeGenerator/BasePDDLCodeGenerator.cpp" "src/SASCodeGenerator/SASCodeGenerator.h" "src/SASCodeGenerator/SASCodeGenerator.cpp" "src/FileVerifier/FileVerifier.h" "src/FileVerifier/FileVerifier.cpp")
add_executable (P7 "src/P7.cpp" ${SOURCES})
target_include_directories(P7 PRIVATE "PDDLParser")

file(COPY Data DESTINATION ${CMAKE_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)