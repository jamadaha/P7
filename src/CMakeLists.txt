add_executable(P7 "P7.cpp")
target_link_libraries(P7 
    PRIVATE
        RunReport
        Config
        StringHelper
        ConsoleHelper
        PathChecker
        PDDLCodeGenerator
        CommonInterface
        PlanValidator
        Reformulator
        PDDLParser
        IntermediatePDDL
        PathChecker
        DownwardRunner
        FileHelper
        Walker
        WalkerPathVerifyer
        JointPaths
        ActionGenerator
        Hashes
        ProgressBarHelper
        MacroGenerator
        Regressor
        PartialActionGenerator
        SAS)

add_executable(P7Lab "P7Lab.cpp")
