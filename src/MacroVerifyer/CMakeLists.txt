add_library(MacroVerifyer "MacroVerifyer.cpp")
target_sources(MacroVerifyer
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/MacroVerifyer.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/MacroVerifyer.hh)
target_include_directories(MacroVerifyer
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(MacroVerifyer Hashes)