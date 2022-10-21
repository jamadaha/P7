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
include(Test/Walker/CMakeLists.txt)
include(Test/Walker/DepthFunctions/CMakeLists.txt)
include(Test/IntermediatePDDL/CMakeLists.txt)
include(Test/PlanValidators/CMakeLists.txt)
include(Test/Helpers/CMakeLists.txt)
include(Test/DownwardRunner/CMakeLists.txt)
