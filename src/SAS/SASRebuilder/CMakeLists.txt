add_library(SASRebuilder "SASRebuilder.cpp")
target_sources(SASRebuilder
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/SASRebuilder.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/SASRebuilder.hh)
target_include_directories(SASRebuilder
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
