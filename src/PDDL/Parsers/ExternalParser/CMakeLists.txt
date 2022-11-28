add_library(ExternalPDDLParser "action.cc" "domain.cc" "location.hh" "pddldriver.cc" "pddllex.yy.cc" "pddlparser.tab.cc" "position.hh" "predicate.cc" "problem.cc" "stack.hh")
target_include_directories(ExternalPDDLParser
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
