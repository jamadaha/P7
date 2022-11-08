add_library(Reformulator "BaseReformulator.cpp")
target_sources(Reformulator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/BaseReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/BaseWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/GreedyWalkerReformulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SameOutputReformulator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BaseReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/BaseWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/Walkers/GreedyWalkerReformulator.hh
        ${CMAKE_CURRENT_LIST_DIR}/SameOutputReformulator.hh)
target_include_directories(Reformulator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Reformulator MacroGenerator)