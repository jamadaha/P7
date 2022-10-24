add_library(EntanglementFinder "EntanglementFinder.cpp")
target_sources(Config
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementFinder.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementFinder.hh)
target_include_directories(EntanglementFinder
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})