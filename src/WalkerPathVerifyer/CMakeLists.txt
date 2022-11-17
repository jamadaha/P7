add_library(WalkerPathVerifyer "WalkerPathVerifyer.cpp")
target_sources(WalkerPathVerifyer
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/WalkerPathVerifyer.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/WalkerPathVerifyer.hh)
target_include_directories(WalkerPathVerifyer
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(WalkerPathVerifyer
    PRIVATE
        IntermediatePDDL
        Config
        Hashes)