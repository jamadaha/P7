add_library(Heuristics "GreedyHeuristic.hh" "GreedyHeuristic.cpp" "BaseHeuristic.hh")
target_sources(Heuristics
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/GreedyHeuristic.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/GreedyHeuristic.hh)
target_include_directories(Heuristics
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})