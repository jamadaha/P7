add_executable(P7 "P7.cpp")
target_link_libraries(P7 
    PRIVATE
        RunReport
        Config
        StringHelper
        ConsoleHelper
        PathChecker
        PDDL
        CommonInterface
        PlanValidator
        Reformulator
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
        MacroVerifyer
        SAS)

add_executable(P7Lab "P7Lab.cpp")
