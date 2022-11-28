add_library(Regressor "BaseRegressor.cpp")
target_sources(Regressor
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/BaseRegressor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Regressor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PartialRegressor.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BaseRegressor.hh
        ${CMAKE_CURRENT_LIST_DIR}/Regressor.hh
        ${CMAKE_CURRENT_LIST_DIR}/PartialRegressor.hh)
target_include_directories(Regressor
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Regressor
    PRIVATE
        PDDL
        Config
        Hashes)
