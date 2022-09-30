find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

include(CTest)
include(Catch)
#set(CMAKE_CTEST_ARGUMENTS "--verbose")

# Tests
include(Test/SASParser/CMakeLists.txt)
include(Test/PDDLCodeGenerator/CMakeLists.txt)
include(Test/PDDLParser/CMakeLists.txt)