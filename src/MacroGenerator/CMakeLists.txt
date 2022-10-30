add_library(MacroGenerator "MacroGenerator.cpp")
target_sources(MacroGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/MacroGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/InstanceGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Macro.hh
        ${CMAKE_CURRENT_LIST_DIR}/MacroGenerator.hh
        ${CMAKE_CURRENT_LIST_DIR}/GroundedAction.hh
        ${CMAKE_CURRENT_LIST_DIR}/InstanceGenerator.hh)
target_include_directories(MacroGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(MacroGenerator Hashes)