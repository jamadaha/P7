add_library(Walker "Variants/WalkerGreedy.cpp")
target_sources(Walker
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerGreedy.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerGreedyResume.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerHillClimber.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerQueue.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerProbe.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerStepBack.cpp
        ${CMAKE_CURRENT_LIST_DIR}/WalkerBuilder.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Path.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerGreedy.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerGreedyResume.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerHillClimber.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerQueue.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerProbe.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerStepBack.hpp
        ${CMAKE_CURRENT_LIST_DIR}/BaseWalker.hh
        ${CMAKE_CURRENT_LIST_DIR}/Path.hh
        ${CMAKE_CURRENT_LIST_DIR}/WalkerBuilder.hpp)
target_include_directories(Walker
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Walker
    PRIVATE
        PDDL
        Config
        Hashes)

add_library(ActionGenerator "ActionGenerator.cpp")
target_sources(ActionGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator2.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator2.hpp)
target_include_directories(ActionGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(ActionGenerator AlgorithmHelper)