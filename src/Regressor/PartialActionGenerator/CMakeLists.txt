add_library(PartialActionGenerator "PartialActionGenerator.cpp")
target_sources(PartialActionGenerator
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/PartialActionGenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PartialActionConverter.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PartialAction.hh
        ${CMAKE_CURRENT_LIST_DIR}/PartialActionGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/PartialActionConverter.hh)
target_include_directories(PartialActionGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(PartialActionGenerator
    PRIVATE
        PDDL
        AlgorithmHelper)
