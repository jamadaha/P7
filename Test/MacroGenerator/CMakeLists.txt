add_executable(Tests-MacroGenerator Test/MacroGenerator/MacroGenerator.cpp)
target_link_libraries(Tests-MacroGenerator
    PRIVATE 
        Catch2::Catch2WithMain
        MacroGenerator)

catch_discover_tests(Tests-MacroGenerator)
