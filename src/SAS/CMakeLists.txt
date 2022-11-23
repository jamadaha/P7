add_library(SAS "SASCodeGenerator.cpp")
target_sources(SAS
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/SASCodeGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/SASCodeGenerator.hh)
target_include_directories(SAS
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})