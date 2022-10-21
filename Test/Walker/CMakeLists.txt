add_executable(Tests-ActionGenerator Test/Walker/ActionGenerator.cpp ${SOURCES})
target_link_libraries(Tests-ActionGenerator 
    PRIVATE 
        Catch2::Catch2WithMain
        ActionGenerator)

catch_discover_tests(Tests-ActionGenerator)
