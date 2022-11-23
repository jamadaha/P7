add_library(SAS "CodeGenerator/CodeGenerator.cpp" "Parser/Parser.cpp" "Rebuilder/Rebuilder.cpp")
target_sources(SAS
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerator/CodeGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Parser/Parser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Rebuilder/Rebuilder.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/SASAction.hh
        ${CMAKE_CURRENT_LIST_DIR}/SASPlan.hh
        ${CMAKE_CURRENT_LIST_DIR}/Parser/Parser.hh
        ${CMAKE_CURRENT_LIST_DIR}/Rebuilder/Rebuilder.hh
        ${CMAKE_CURRENT_LIST_DIR}/CodeGenerator/CodeGenerator.hh)
target_include_directories(SAS
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})