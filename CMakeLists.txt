# CMakeList.txt : CMake project for P7, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("P7")

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
	"src/PDDLCodeGenerator/PDDLCodeGenerator.h" "src/PDDLCodeGenerator/PDDLCodeGenerator.cpp" "src/PDDLCodeGenerator/PDDLDomainCodeGenerator.h" "src/PDDLCodeGenerator/PDDLDomainCodeGenerator.cpp" "src/PDDLCodeGenerator/PDDLProblemCodeGenerator.h" "src/PDDLCodeGenerator/PDDLProblemCodeGenerator.cpp")
add_executable (P7 "src/P7.cpp" ${SOURCES})
target_include_directories(P7 PRIVATE "PDDLParser")
file(COPY "Data/gripper.pddl" "Data/gripper-4.pddl" "Data/gripper-typed.pddl" "Data/test_sas_plan"
     DESTINATION ${CMAKE_BINARY_DIR}/Data)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET P7 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
