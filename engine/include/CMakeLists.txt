add_library(
    FIXEngineLib
    FixApplication.hpp
)
set_target_properties(FIXEngineLib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
    FIXEngineLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    FIXEngineLib
    PUBLIC    
        quickfix::quickfix
)
