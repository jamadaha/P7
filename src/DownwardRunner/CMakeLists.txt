add_library(DownwardRunner "DownwardRunner.cpp")
target_sources(DownwardRunner
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/DownwardRunner.cpp
        ${CMAKE_CURRENT_LIST_DIR}/H2Runner.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/DownwardRunner.hh
        ${CMAKE_CURRENT_LIST_DIR}/H2Runner.hh)
target_include_directories(DownwardRunner
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(DownwardRunner Config)