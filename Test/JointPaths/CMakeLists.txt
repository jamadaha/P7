add_executable(Tests-JointPaths "Test/JointPaths/FinderTests.cpp" "Test/JointPaths/EvaluatorTests.cpp" "Test/JointPaths/HashesTests.cpp")
target_link_libraries(Tests-JointPaths 
    PRIVATE 
        Catch2::Catch2WithMain
        JointPaths
        PDDL
        ProgressBarHelper)

catch_discover_tests(Tests-JointPaths)
