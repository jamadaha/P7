add_library(Macros "Generators/Generator.cpp" "Instantiators/Instantiator.cpp")
target_sources(Macros
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Generators/Generator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Instantiators/Instantiator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Macro.hh
        ${CMAKE_CURRENT_LIST_DIR}/Generators/Generator.hh
        ${CMAKE_CURRENT_LIST_DIR}/GroundedAction.hh
        ${CMAKE_CURRENT_LIST_DIR}/GroundedLiteral.hh
        ${CMAKE_CURRENT_LIST_DIR}/Instantiators/Instantiator.hh)
target_include_directories(Macros
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Macros Hashes)