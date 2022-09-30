find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

include(CTest)
include(Catch)
#set(CMAKE_CTEST_ARGUMENTS "--verbose")

project(Tests-All VERSION 0.1.0)

# Tests
include(Test/SASParser/CMakeLists.txt)
include(Test/PDDLCodeGenerator/CMakeLists.txt)
include(Test/PDDLParser/CMakeLists.txt)

add_executable(Test-All 
	"Test/PDDLCodeGenerator/PDDLCodeGenerator.cpp" 
	"Test/PDDLParser/PDDLParser.cpp"
	"Test/SASParser/SASParser.cpp"
	${SOURCES})
target_link_libraries(Test-All PRIVATE Catch2::Catch2WithMain)