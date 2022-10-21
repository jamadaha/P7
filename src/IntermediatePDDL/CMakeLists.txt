add_library(IntermediatePDDL "PDDLConverter.cpp" "PDDLAction.hh" "PDDLActionInstance.hh" "PDDLDomain.hh" "PDDLInstance.hh" "PDDLLiteral.hh" "PDDLPredicate.hh" "PDDLProblem.hh" "PDDLState.hh")
target_sources(IntermediatePDDL
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/PDDLConverter.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PDDLConverter.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLAction.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLActionInstance.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLDomain.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLInstance.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLLiteral.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLPredicate.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLProblem.hh
        ${CMAKE_CURRENT_LIST_DIR}/PDDLState.hh)
target_include_directories(IntermediatePDDL
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})