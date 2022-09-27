add_executable(SASParser Test/SASParser/SASParser.cpp ${SOURCES})
target_link_libraries(SASParser PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(SASParser)
