add_library(ActionGenerator "BaseActionGenerator.cpp")
target_sources(ActionGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/BaseActionGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ActionGeneratorRegressing.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BaseActionGenerator.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.hpp
        ${CMAKE_CURRENT_LIST_DIR}/ActionGeneratorRegressing.hpp)
target_include_directories(ActionGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(ActionGenerator AlgorithmHelper)