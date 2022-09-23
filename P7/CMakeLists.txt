# CMakeList.txt : CMake project for P7, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("P7")

# Add source to this project's executable.
set(SOURCES 
	"PDDLParser/action.cc" "PDDLParser/action.hh" 
	"PDDLParser/pddldriver.cc" "PDDLParser/pddldriver.hh"
	"PDDLParser/domain.cc" "PDDLParser/domain.hh"
	"PDDLParser/location.hh"
	"PDDLParser/pddllex.yy.cc"
	"PDDLParser/pddlparser.tab.cc" "PDDLParser/pddlparser.tab.hh"
	"PDDLParser/position.hh"
	"PDDLParser/predicate.cc" "PDDLParser/predicate.hh"
	"PDDLParser/problem.cc" "PDDLParser/problem.hh"
	"PDDLParser/stack.hh"	)
add_executable (P7 "P7.cpp" "P7.h" ${SOURCES})
target_include_directories(P7 PRIVATE "PDDLParser")
file(COPY "Data/gripper.pddl" "Data/gripper-4.pddl"
     DESTINATION ${CMAKE_BINARY_DIR}/Data)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET P7 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
