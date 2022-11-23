add_executable(Tests-SAS "Test/SAS/CodeGenerator/CodeGeneratorTests.cpp" "Test/SAS/Parser/ParserTests.cpp")
target_link_libraries(Tests-SAS 
    PRIVATE 
        Catch2::Catch2WithMain
        SAS
        StringHelper)
catch_discover_tests(Tests-SAS) 