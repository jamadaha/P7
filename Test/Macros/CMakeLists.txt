add_executable(Tests-Macros "Test/Macros/Generators/GeneratorTests.cpp" "Test/Macros/Instantiators/InstantiatorTests.cpp")
target_link_libraries(Tests-Macros
    PRIVATE 
        Catch2::Catch2WithMain
        Macros
        PDDL)

catch_discover_tests(Tests-Macros)
