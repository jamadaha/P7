add_executable(Tests-PDDL "Test/PDDL/CodeGenerators/CodeGeneratorTests.cpp" "Test/PDDL/Parsers/ConverterTests.cpp")
target_link_libraries(Tests-PDDL 
    PRIVATE 
        Catch2::Catch2WithMain
        PDDL
        StringHelper)

file(COPY "Test/PDDL/CodeGenerators/TestFiles" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "Test/PDDL/Parsers/TestFiles" DESTINATION ${CMAKE_BINARY_DIR})

catch_discover_tests(Tests-PDDL)
