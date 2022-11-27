add_library(Macros "Generator/Generator.cpp" "Instantiator/Instantiator.cpp")
target_sources(Macros
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Generator/Generator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Instantiator/Instantiator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Macro.hh
        ${CMAKE_CURRENT_LIST_DIR}/Generator/Generator.hh
        ${CMAKE_CURRENT_LIST_DIR}/GroundedAction.hh
        ${CMAKE_CURRENT_LIST_DIR}/GroundedLiteral.hh
        ${CMAKE_CURRENT_LIST_DIR}/Instantiator/Instantiator.hh)
target_include_directories(Macros
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Macros Hashes)