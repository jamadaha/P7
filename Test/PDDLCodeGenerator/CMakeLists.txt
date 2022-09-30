add_executable(PDDLCodeGenerator Test/PDDLCodeGenerator/PDDLCodeGenerator.cpp ${SOURCES})
target_link_libraries(PDDLCodeGenerator PRIVATE Catch2::Catch2WithMain)

file(COPY Test/PDDLCodeGenerator/TestFiles DESTINATION ${CMAKE_BINARY_DIR})

catch_discover_tests(PDDLCodeGenerator)
