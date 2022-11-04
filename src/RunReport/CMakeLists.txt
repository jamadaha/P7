add_library(RunReport "RunReport.cpp" "CompareReport.cpp")
target_sources(RunReport
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/RunReport.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CompareReport.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/RunReport.hh
        ${CMAKE_CURRENT_LIST_DIR}/CompareReport.hh)
target_include_directories(RunReport
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})