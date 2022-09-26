find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

include(CTest)
include(Catch)
#set(CMAKE_CTEST_ARGUMENTS "--verbose")


# Tests
add_executable(Test Test/Test.cpp)
target_link_libraries(Test PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(Test)