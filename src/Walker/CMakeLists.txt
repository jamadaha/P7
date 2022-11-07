add_library(Walker "Variants/Walker.cpp")
target_sources(Walker
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Variants/Walker.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerResume.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerQueue.cpp
        ${CMAKE_CURRENT_LIST_DIR}/WalkerBuilder.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Variants/Walker.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerResume.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Variants/WalkerQueue.hpp
        ${CMAKE_CURRENT_LIST_DIR}/BaseWalker.hh
        ${CMAKE_CURRENT_LIST_DIR}/Path.hpp
        ${CMAKE_CURRENT_LIST_DIR}/WalkerBuilder.hpp)
target_include_directories(Walker
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Walker
    PRIVATE
        IntermediatePDDL
        Config
        Hashes)

add_library(ActionGenerator "ActionGenerator.cpp")
target_sources(ActionGenerator
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ActionGenerator.hpp)
target_include_directories(ActionGenerator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(ActionGenerator AlgorithmHelper)