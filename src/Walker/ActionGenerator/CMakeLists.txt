add_library(ActionGenerator "ActionGenerator.cpp")
target_sources(ActionGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/BinaryFactVerifier.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UnaryFactVerifier.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.hpp
        ${CMAKE_CURRENT_LIST_DIR}/BinaryFactVerifier.hpp
        ${CMAKE_CURRENT_LIST_DIR}/UnaryFactVerifier.hpp)
target_include_directories(ActionGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(ActionGenerator AlgorithmHelper)