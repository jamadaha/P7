add_library(PDDL 
    "Action.cpp" "ActionInstance.cpp" "Domain.hh" "Instance.hh" "Literal.hh" "Predicate.hh" "Problem.hh" "State.cpp" 
    "CodeGenerators/BaseCodeGenerator.cpp" "CodeGenerators/CodeGenerator.cpp" "CodeGenerators/DomainCodeGenerator.cpp" "CodeGenerators/ProblemCodeGenerator.cpp" 
    "Parsers/Converter.cpp" 
    "Parsers/ExternalParser.cpp"
    "Parsers/ExternalParser/action.cc" "Parsers/ExternalParser/domain.cc" "Parsers/ExternalParser/location.hh" "Parsers/ExternalParser/pddldriver.cc" "Parsers/ExternalParser/pddllex.yy.cc" "Parsers/ExternalParser/pddlparser.tab.cc" "Parsers/ExternalParser/position.hh" "Parsers/ExternalParser/predicate.cc" "Parsers/ExternalParser/problem.cc" "Parsers/ExternalParser/stack.hh"
)
target_sources(PDDL
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Parsers/Converter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Action.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ActionInstance.cpp
        ${CMAKE_CURRENT_LIST_DIR}/State.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerators/BaseCodeGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerators/CodeGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerators/DomainCodeGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerators/ProblemCodeGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Parsers/ExternalParser.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Parsers/Converter.hh
        ${CMAKE_CURRENT_LIST_DIR}/Action.hh
        ${CMAKE_CURRENT_LIST_DIR}/ActionInstance.hh
        ${CMAKE_CURRENT_LIST_DIR}/Domain.hh
        ${CMAKE_CURRENT_LIST_DIR}/Instance.hh
        ${CMAKE_CURRENT_LIST_DIR}/Literal.hh
        ${CMAKE_CURRENT_LIST_DIR}/Mutex.hh
        ${CMAKE_CURRENT_LIST_DIR}/Predicate.hh
        ${CMAKE_CURRENT_LIST_DIR}/Problem.hh
        ${CMAKE_CURRENT_LIST_DIR}/State.hh
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerators/BaseCodeGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerators/CodeGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerators/DomainCodeGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerators/ProblemCodeGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Parsers/ExternalParser.hh
)

target_include_directories(PDDL
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})