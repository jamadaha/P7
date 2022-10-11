add_executable(Tests-PDDLTypes Test/PDDLTypes/PDDLTypes.cpp ${SOURCES})
target_link_libraries(Tests-PDDLTypes PRIVATE Catch2::Catch2WithMain)

file(COPY Test/PDDLTypes/TestFiles DESTINATION ${CMAKE_BINARY_DIR})

catch_discover_tests(Tests-PDDLTypes)
