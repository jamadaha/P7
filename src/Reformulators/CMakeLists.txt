add_library(Reformulator "BaseReformulator.hh")
target_sources(Reformulator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/BaseWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/GreedyWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/GreedyResumeWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/QueueWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/ProbeWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/RegressiveWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SameOutputReformulator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BaseReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/BaseWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/GreedyWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/GreedyResumeWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/QueueWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/ProbeWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/RegressiveWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/SameOutputReformulator.hh)
target_include_directories(Reformulator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Reformulator MacroGenerator)