add_executable(Tests-PDDLParser Test/PDDLParser/PDDLParser.cpp ${SOURCES})
target_link_libraries(Tests-PDDLParser PRIVATE Catch2::Catch2WithMain)

file(COPY Test/PDDLParser/TestFiles DESTINATION ${CMAKE_BINARY_DIR})

catch_discover_tests(Tests-PDDLParser)
