add_executable(
    FIXEngine
    main.cpp
)

target_link_libraries(
    FIXEngine
    PRIVATE
        FIXEngineLib    
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../../spec/FIXT11.xml"
    $<TARGET_FILE_DIR:FIXEngine>
)

add_custom_command(
    TARGET FIXEngine 
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/../../spec/FIX50SP2.xml"
    $<TARGET_FILE_DIR:FIXEngine>
)