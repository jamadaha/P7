add_library(JointPaths "JointPath.cpp" "Evaluator/Evaluator.cpp" "Finder/Finder.cpp")
target_sources(JointPaths
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Finder/Finder.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Evaluator/Evaluator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Finder/Finder.hh
        ${CMAKE_CURRENT_LIST_DIR}/Evaluator/Evaluator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Evaluator/EvaluationModifiers.hh
        ${CMAKE_CURRENT_LIST_DIR}/JointPath.hh)
target_include_directories(JointPaths
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})