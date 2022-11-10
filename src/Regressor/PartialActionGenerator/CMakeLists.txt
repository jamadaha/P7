add_library(PartialActionGenerator "PartialActionGenerator.cpp")
target_sources(PartialActionGenerator
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/PartialActionGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PartialAction.hh
        ${CMAKE_CURRENT_LIST_DIR}/PartialActionGenerator.hh)
target_include_directories(PartialActionGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(PartialActionGenerator
    PRIVATE
        IntermediatePDDL
        AlgorithmHelper)
