add_executable(Tests-PDDLParser Test/PDDLParser/PDDLParser.cpp "Test/PDDLParser/TestFiles/gripper.pddl" "Test/PDDLParser/TestFiles/gripper-4.pddl" ${SOURCES})
target_link_libraries(Tests-PDDLParser PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(Tests-PDDLParser)
