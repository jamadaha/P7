add_library(EntanglementFinder "EntanglementFinder.cpp" "EntanglementOccurance.cpp" "EntanglementEvaluator.cpp")
target_sources(EntanglementFinder
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementFinder.cpp
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementEvaluator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementFinder.hh
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementEvaluator.hh
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementEvaluatorModifiers.hh
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementOccurance.hh)
target_include_directories(EntanglementFinder
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})