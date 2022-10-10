find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

include(CTest)
include(Catch)
#set(CMAKE_CTEST_ARGUMENTS "--verbose")

# Tests
include(Test/SASParser/CMakeLists.txt)
include(Test/SASCodeGenerator/CMakeLists.txt)
include(Test/PDDLCodeGenerator/CMakeLists.txt)
include(Test/PDDLParser/CMakeLists.txt)
include(Test/PDDLTypes/CMakeLists.txt)
include(Test/DepthFunctions/CMakeLists.txt)
include(Test/PlanValidators/CMakeLists.txt)

# To run all tests
add_executable(Test-All 
	"Test/PDDLCodeGenerator/PDDLCodeGenerator.cpp"
	"Test/PDDLParser/PDDLParser.cpp"
	"Test/PDDLTypes/PDDLTypes.cpp"
	"Test/SASParser/SASParser.cpp"
	"Test/SASCodeGenerator/SASCodeGenerator.cpp"
	"Test/DepthFunctions/ConstantDepthFunction.cpp"
	"Test/DepthFunctions/ObjectActionDepthFunction.cpp"
	"Test/PlanValidators/PlanValidator.cpp"
	${SOURCES})
target_link_libraries(Test-All PRIVATE Catch2::Catch2WithMain)