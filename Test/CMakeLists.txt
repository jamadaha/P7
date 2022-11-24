find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

include(CTest)
include(Catch)
#set(CMAKE_CTEST_ARGUMENTS "--verbose")

# Tests
include(Test/SAS/CMakeLists.txt)
include(Test/PDDLCodeGenerator/CMakeLists.txt)
include(Test/PDDLParser/CMakeLists.txt)
include(Test/Walker/CMakeLists.txt)
include(Test/IntermediatePDDL/CMakeLists.txt)
include(Test/PlanValidators/CMakeLists.txt)
include(Test/Helpers/CMakeLists.txt)
include(Test/DownwardRunner/CMakeLists.txt)
include(Test/EntanglementFinder/CMakeLists.txt)
include(Test/MacroGenerator/CMakeLists.txt)

add_executable(Test-All 
	"Test/PDDLCodeGenerator/PDDLCodeGenerator.cpp"
	"Test/PDDLParser/PDDLParser.cpp"
	"Test/IntermediatePDDL/IntermediatePDDL.cpp"
	"Test/SAS/Parser/ParserTests.cpp"
	"Test/SAS/CodeGenerator/CodeGeneratorTests.cpp"
	"Test/SAS/Rebuilder/RebuilderTests.cpp"
	"Test/Walker/ActionGenerator.cpp"
	"Test/Walker/Walker.cpp"
	"Test/PlanValidators/PlanValidator.cpp"
	"Test/Helpers/StringHelper.cpp"
	"Test/EntanglementFinder/EntanglementFinder.cpp"
	"Test/EntanglementFinder/Hashes.cpp"
	"Test/DownwardRunner/DownwardRunner.cpp"
    "Test/MacroGenerator/MacroGenerator.cpp")
target_link_libraries(Test-All 
	PRIVATE 
		Catch2::Catch2WithMain
		RunReport
        Config
        StringHelper
        ConsoleHelper
        FileVerifier
        PathChecker
        PDDLCodeGenerator
        CommonInterface
        PlanValidator
        Reformulator
        SAS
        PDDLParser
        IntermediatePDDL
        PathChecker
        DownwardRunner
        FileHelper
        EntanglementFinder
        Walker
        ActionGenerator
        MacroGenerator)