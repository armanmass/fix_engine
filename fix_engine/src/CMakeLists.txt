add_executable(
    FIXEngine
    FixEngine.cpp
    OrderSender.cpp
)

target_link_libraries(
    FIXEngine
    PRIVATE
        FIXEngineLib
        Common
)

add_custom_command(
    TARGET FIXEngine 
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../server.cfg"
    $<TARGET_FILE_DIR:FIXEngine>
)

add_custom_command(
    TARGET FIXEngine 
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../common/spec/FIXT11.xml"
    $<TARGET_FILE_DIR:FIXEngine>
)

add_custom_command(
    TARGET FIXEngine 
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../common/spec/FIX50SP2.xml"
    $<TARGET_FILE_DIR:FIXEngine>
)