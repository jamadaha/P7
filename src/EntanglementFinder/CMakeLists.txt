add_library(EntanglementFinder "EntanglementFinder.cpp" "EntanglementOccurance.cpp")
target_sources(Config
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementFinder.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementFinder.hh
        ${CMAKE_CURRENT_LIST_DIR}/EntanglementOccurance.hh)
target_include_directories(EntanglementFinder
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})