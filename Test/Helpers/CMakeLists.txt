add_executable(Tests-Helpers "Test/Helpers/StringHelper.cpp" "Test/Helpers/HashesTests.cpp")
target_link_libraries(Tests-Helpers 
    PRIVATE 
        Catch2::Catch2WithMain
        StringHelper
        Hashes)

catch_discover_tests(Tests-Helpers)
