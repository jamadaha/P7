find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

include(CTest)
include(Catch)
#set(CMAKE_CTEST_ARGUMENTS "--verbose")

# Tests
include(Test/SAS/CMakeLists.txt)
include(Test/PDDL/CMakeLists.txt)
include(Test/Walker/CMakeLists.txt)
include(Test/PlanValidators/CMakeLists.txt)
include(Test/Helpers/CMakeLists.txt)
include(Test/DownwardRunner/CMakeLists.txt)
include(Test/JointPaths/CMakeLists.txt)
include(Test/Macros/CMakeLists.txt)

add_executable(Test-All 
	"Test/PDDL/CodeGenerators/CodeGeneratorTests.cpp"
	"Test/PDDL/Parsers/ConverterTests.cpp"
	"Test/SAS/Parser/ParserTests.cpp"
	"Test/SAS/CodeGenerator/CodeGeneratorTests.cpp"
	"Test/SAS/Rebuilder/RebuilderTests.cpp"
	"Test/Walker/ActionGenerator.cpp"
	"Test/Walker/Walker.cpp"
	"Test/PlanValidators/PlanValidator.cpp"
	"Test/Helpers/StringHelper.cpp"
	"Test/JointPaths/FinderTests.cpp"
	"Test/JointPaths/EvaluatorTests.cpp"
	"Test/JointPaths/HashesTests.cpp"
	"Test/DownwardRunner/DownwardRunner.cpp"
    "Test/Macros/Generators/GeneratorTests.cpp"
    "Test/Macros/Instantiators/InstantiatorTests.cpp"
)
target_link_libraries(Test-All 
	PRIVATE 
		Catch2::Catch2WithMain
		RunReport
        Config
        StringHelper
        ConsoleHelper
        PathChecker
        PDDL
        CommonInterface
        PlanValidator
        Reformulator
        SAS
        PathChecker
        DownwardRunner
        FileHelper
        JointPaths
        Walker
        ActionGenerator
        Macros)